// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <vector>
#include "CoreMinimal.h"
#include "Gun.h"

/**
 * @brief Manager for the player's weapons. \n
 * Contains references to all the player's weapons, and facilitates interactions between the player controller and it.
 */
class COLLAPSE_API GunManager
{
public:
	GunManager();
	~GunManager();

	//Weapon Stuffs
	/**
	 * @brief helper function to fire the currently equipped gun.
	 */
	void FireCurrentWeapon();

	/**
	 * @brief helper function to reload the currently equipped gun.
	 */
	void ReloadCurrentWeapon();

	/**
	 * @brief helper function to use secondary on the currently equipped gun.
	 */
	void SecondaryCurrentWeapon();

	void SelectWeapon(UINT weapon);

private:
	//An array of all of our guns. Four slots for the four guns.
	UGun Guns[4];

	
	int currentIndex = -1;
};
