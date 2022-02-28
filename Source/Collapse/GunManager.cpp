// Author: Natalie Soltis for Collapse.


#include "GunManager.h"

#include <string>

// Sets default values
AGunManager::AGunManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGunManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunManager::FireCurrent()
{
}

void AGunManager::FireSecCurrent()
{
}

void AGunManager::ReloadCurrent()
{
}

void AGunManager::SwapTo(int GunIndex)
{
	std::string s = std::to_string(GunIndex);
	printf(s.c_str());
}

