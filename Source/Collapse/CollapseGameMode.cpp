// Copyright Epic Games, Inc. All Rights Reserved.

#include "CollapseGameMode.h"
#include "CollapseHUD.h"
#include "CollapseCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACollapseGameMode::ACollapseGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACollapseHUD::StaticClass();
}
