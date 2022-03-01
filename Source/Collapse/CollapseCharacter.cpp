// Copyright Epic Games, Inc. All Rights Reserved.

#include "CollapseCharacter.h"

#include <iostream>
#include <GeomUtils/GuContactBuffer.h>

#include "CollapseProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "GunManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ACollapseCharacter

ACollapseCharacter::ACollapseCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false); // otherwise won't be visible in the multiplayer
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;

	//Set up our Gun manager etc
}

void ACollapseCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
	                          TEXT("GripPoint"));


	Mesh1P->SetHiddenInGame(false, true);

	GunManager = GetWorld()->SpawnActor<UGunManager>(FVector::ZeroVector, FRotator::ZeroRotator);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACollapseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACollapseCharacter::OnFire);
	PlayerInputComponent->BindAction("SecondaryFire", IE_Pressed, this, &ACollapseCharacter::OnSecondary);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ACollapseCharacter::OnReload);
	PlayerInputComponent->BindAction("SelGun1", IE_Pressed, this, &ACollapseCharacter::OnSwitchGun1);
	PlayerInputComponent->BindAction("SelGun2", IE_Pressed, this, &ACollapseCharacter::OnSwitchGun2);
	PlayerInputComponent->BindAction("SelGun3", IE_Pressed, this, &ACollapseCharacter::OnSwitchGun3);
	PlayerInputComponent->BindAction("SelGun4", IE_Pressed, this, &ACollapseCharacter::OnSwitchGun4);

	
	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ACollapseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACollapseCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACollapseCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACollapseCharacter::LookUpAtRate);
}

void ACollapseCharacter::OnFire()
{
	// try and fire a projectile
	// if (ProjectileClass != nullptr)
	// {
	// 	UWorld* const World = GetWorld();
	// 	if (World != nullptr)
	// 	{
	// 		const FRotator SpawnRotation = GetControlRotation();
	// 		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	// 		const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr)
	// 			                               ? FP_MuzzleLocation->GetComponentLocation()
	// 			                               : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
	//
	// 		//Set Spawn Collision Handling Override
	// 		FActorSpawnParameters ActorSpawnParams;
	// 		ActorSpawnParams.SpawnCollisionHandlingOverride =
	// 			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	//
	// 		// spawn the projectile at the muzzle
	// 		World->SpawnActor<ACollapseProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	// 	}
	// }
	// try and play the sound if specified
	// if (FireSound != nullptr)
	// {
	// 	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	// }
	//
	// // try and play a firing animation if specified
	// if (FireAnimation != nullptr)
	// {
	// 	// Get the animation object for the arms mesh
	// 	UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
	// 	if (AnimInstance != nullptr)
	// 	{
	// 		AnimInstance->Montage_Play(FireAnimation, 1.f);
	// 	}
	// }

	GunManager->FireCurrent();
}

void ACollapseCharacter::OnSecondary()
{
	GunManager->FireCurrentSec();
}

void ACollapseCharacter::OnReload()
{
	GunManager->ReloadCurrent();
}

void ACollapseCharacter::OnSwitchGun1()
{
	GunManager->SwapTo(1);
}

void ACollapseCharacter::OnSwitchGun2()
{
	GunManager->SwapTo(2);

}

void ACollapseCharacter::OnSwitchGun3()
{
	GunManager->SwapTo(3);

}

void ACollapseCharacter::OnSwitchGun4()
{
	GunManager->SwapTo(4);

}

void ACollapseCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ACollapseCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ACollapseCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACollapseCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
