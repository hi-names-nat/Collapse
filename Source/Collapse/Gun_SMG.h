// Author: Natalie Soltis for Collapse.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Gun_SMG.generated.h"

/**
 * 
 */
UCLASS()
class COLLAPSE_API UGun_SMG : public UGun
{
	GENERATED_BODY()
	virtual void Fire() override;
	virtual void Reload() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ACollapseProjectile> ProjectileClass;
	
};
