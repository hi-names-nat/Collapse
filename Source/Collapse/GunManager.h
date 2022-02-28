// Author: Natalie Soltis for Collapse.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunManager.generated.h"

class UGun;

UCLASS()
class COLLAPSE_API AGunManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunManager();

	UGun* guns[4];
	unsigned numGuns = 4;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireCurrent();

	void FireSecCurrent();

	void ReloadCurrent();
	
	void SwapTo(int GunIndex);

};
