// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <memory>
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <vector>
#include "CollapseCharacter.generated.h"


class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UBaseGun;

//Unneeded.
class UAnimMontage;
class USoundBase;
class WeaponManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadItem);

struct GunManager
{
	//Do not access directly
	std::vector<std::shared_ptr<UBaseGun>> list_guns;

	std::shared_ptr<UBaseGun> GetGunAt(uint8 index);

	std::shared_ptr<UBaseGun> nextGun(uint8 index) { int i = index + 1; if (i<0) return list_guns[0]; else return list_guns[i]; }

	std::shared_ptr<UBaseGun> previousGun(uint8 index) { int i = index - 1; if (i<0) return list_guns[list_guns.size()-1]; else return list_guns[i];}
};

UCLASS(config=Game)
class ACollapseCharacter : public ACharacter
{
	GENERATED_BODY()
private:
	
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	UBaseGun* CurrentGun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	float timer = .1f;
	

public:
	GunManager guns;
	
	ACollapseCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	// /** Projectile class to spawn */
	// UPROPERTY(EditDefaultsOnly, Category=Projectile)
	// TSubclassOf<class ACollapseProjectile> ProjectileClass;

	// /** Sound to play each time we fire */
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	// USoundBase* FireSound;
	//
	// /** AnimMontage to play each time we fire */
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	// UAnimMontage* FireAnimation;

protected:
	/**
	 * @brief 
	 */
	void OnFire();

	void OnFireUp();

	/**
	 * @brief 
	 */
	void OnSecondary();

	/**
	 * @brief 
	 */
	void OnReload();

	/**
	 * @brief 
	 */
	void OnSwitchGun1();

	/**
	 * @brief 
	 */
	void OnSwitchGun2();

	/**
	 * @brief 
	 */
	void OnSwitchGun3();

	/**
	 * @brief 
	 */
	void OnSwitchGun4();
	
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

