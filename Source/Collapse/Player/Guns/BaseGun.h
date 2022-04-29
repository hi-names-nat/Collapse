// Author: Natalie Soltis for Collapse.

#pragma once

#include "CoreMinimal.h"
#include "BaseGun.Generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COLLAPSE_API UBaseGun : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseGun();

	UPROPERTY(BlueprintReadWrite, Category = Status)
	bool Unlocked = false;

	virtual void Reload();
	virtual void Fire();
	virtual void FireSecondary();
	virtual void SwitchedTo();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats, meta = (AllowPrivateAccess = "true"))
	float ShotsPerSecond = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats, meta = (AllowPrivateAccess = "true"))
	int ClipSize = 25;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats, meta = (AllowPrivateAccess = "true"))
	float DamagePerBullet = 1.2f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
