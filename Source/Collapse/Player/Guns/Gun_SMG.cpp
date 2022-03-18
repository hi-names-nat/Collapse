// Author: Natalie Soltis for Collapse.


#include "Gun_SMG.h"
#include "../CollapseProjectile.h"

void UGun_SMG::Fire()
{
	// try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			
			const FRotator SpawnRotation = Cast<APawn>(GetAttachmentRootActor())->GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = Manager->MuzzleLocation;

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;


			// spawn the projectile at the muzzle
		}
	}
	
}


void UGun_SMG::Reload()
{
	
}

void UGun_SMG::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	
}

