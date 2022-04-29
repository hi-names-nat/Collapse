// Author: Natalie Soltis for Collapse.


#include "BaseGun.h"

#include "Camera/CameraActor.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UBaseGun::UBaseGun()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UBaseGun::Reload()
{
	
}

void UBaseGun::Fire()
{
	UE_LOG(LogTemp, Log, TEXT("pew"))

}

void UBaseGun::FireSecondary()
{
	
}

void UBaseGun::SwitchedTo()
{
	
}

// Called when the game starts
void UBaseGun::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBaseGun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{


	
}

