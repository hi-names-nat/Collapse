// Author: Natalie Soltis for Collapse.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GunManager.generated.h"

class UGun;

DECLARE_LOG_CATEGORY_EXTERN(GunManager, Log, All);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COLLAPSE_API UGunManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGunManager();
	FVector MuzzleLocation;

	void SwapTo(int index);
	void UnlockGun(int index);
	void ReloadCurrent();
	void FireCurrent();

	//Will be unused. In for extension later if so needed.
	void FireCurrentSec();

	USceneComponent* Grip;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	UGun* Guns[4];
	UGun* CurrentGun;
};
