// Fill out your copyright notice in the Description page of Project Settings.


#include "GunManager.h"

GunManager::GunManager()
{
}

GunManager::~GunManager()
{
}

void GunManager::FireCurrentWeapon()
{
	unimplemented();
}

void GunManager::ReloadCurrentWeapon()
{
	unimplemented();
}


void GunManager::SecondaryCurrentWeapon()
{
	unimplemented();
}

void GunManager::SelectWeapon(UINT weapon)
{
	if (weapon < 4 && Guns[weapon].Unlocked())
	{
		this->currentIndex = weapon;
	}
}
