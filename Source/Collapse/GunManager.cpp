// Author: Natalie Soltis for Collapse.


#include "GunManager.h"

#include <iostream>
#include <string>

DEFINE_LOG_CATEGORY(GunManager);


// Sets default values for this component's properties
UGunManager::UGunManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UGunManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGunManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGunManager::SwapTo(int index)
{
	UE_LOG(GunManager, Log, TEXT("Swapping to: %d..."), index);
}

void UGunManager::ReloadCurrent()
{
	UE_LOG(GunManager, Log, TEXT("Reloading current weapon..."));

}

void UGunManager::FireCurrent()
{
	UE_LOG(GunManager, Log, TEXT("Firing current weapon..."));

}

void UGunManager::FireCurrentSec()
{
	UE_LOG(GunManager, Log, TEXT("Firing current weapon Secondary..."));

}

