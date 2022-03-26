// Author: Natalie Soltis for Collapse.


#include "GunManager.h"

#include "CollapseCharacter.h"
#include "Guns/Gun_SMG.h"

DEFINE_LOG_CATEGORY(GunManager);


/**
 * @brief Constructor for manager Component built for player.
 */
UGunManager::UGunManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Guns[0] = CreateDefaultSubobject<UGun_SMG>("SMG");
	Guns[0]->SetupAttachment(Grip);
	CurrentGun = nullptr;
	
} // !UGunManger()


void UGunManager::BeginPlay()
{
	Super::BeginPlay();
	
} // !BeginPlay()

/**
 * @brief Swap to the gun at index.
 * @param index The gun to swap to.
 */
void UGunManager::SwapTo(int index)
{
	UE_LOG(GunManager, Log, TEXT("Swapping to: %d..."), index);
	if (Guns[index]->Unlocked)
	{
		CurrentGun->SetActive((false));
		CurrentGun = Guns[index];
		CurrentGun->SetActive(true);
		CurrentGun->SwitchedTo();
	}
} // !SwapTo(int)

/**
 * @brief Unlock the gun at index
 * @param index The gun to unlock, as its index.
 */
void UGunManager::UnlockGun(int index)
{
	Guns[index]->Unlocked = true;
	UE_LOG(GunManager, Log, TEXT("Gun %d was unlocked..."), index);
	this->SwapTo(index);
} // !UnlockGun(int)


/**
 * @brief Reload the current weapon.
 */
void UGunManager::ReloadCurrent()
{
	if (!CurrentGun) return;
	UE_LOG(GunManager, Log, TEXT("Reloading current weapon..."));
	CurrentGun->Reload();
} // !ReloadCurrent()

/**
 * @brief Fire the current weapon.
 */
void UGunManager::FireCurrent()
{
	if (!CurrentGun) return;
	UE_LOG(GunManager, Log, TEXT("Firing current weapon..."));
	CurrentGun->Fire();
} // !FireCurrent()

/**
 * @brief Going unused in Collapse.
 */
void UGunManager::FireCurrentSec()
{
	if (!CurrentGun) return;
	UE_LOG(GunManager, Log, TEXT("Firing current weapon Secondary..."));
	CurrentGun->FireSecondary();
} // !FireCurrentSec()

