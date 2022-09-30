// Copyright Epic Games, Inc. All Rights Reserved.

#include "IonTrappersGameMode.h"
#include "IonTrappersHUD.h"
#include "IonTrappersCharacter.h"
#include "UObject/ConstructorHelpers.h"

AIonTrappersGameMode::AIonTrappersGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AIonTrappersHUD::StaticClass();
}
