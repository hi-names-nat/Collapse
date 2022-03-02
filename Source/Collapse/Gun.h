// Author: Natalie Soltis for Collapse.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gun.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COLLAPSE_API UGun : public UMeshComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMesh* WeaponMesh;

	
	

public:	
	// Sets default values for this component's properties
	UGun();

	UPROPERTY(VisibleDefaultsOnly, Category = Gameplay)
	bool Unlocked = false;

	virtual void Reload();
	virtual void Fire();
	virtual void FireSecondary();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
