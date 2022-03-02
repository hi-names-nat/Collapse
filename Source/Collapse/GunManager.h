// Author: Natalie Soltis for Collapse.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gun.h"
#include "GunManager.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(GunManager, Log, All);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COLLAPSE_API UGunManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunManager();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SwapTo(int index);
	void ReloadCurrent();
	void FireCurrent();
	void FireCurrentSec();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	UGun* Guns[4];
};
