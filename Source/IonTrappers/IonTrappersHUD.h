// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IonTrappersHUD.generated.h"

UCLASS()
class AIonTrappersHUD : public AHUD
{
	GENERATED_BODY()

public:
	AIonTrappersHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

