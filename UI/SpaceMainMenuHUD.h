// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "GameFramework/HUD.h"
#include "SpaceMainMenuHUD.generated.h"

/**
 * ASpaceMainMenuHUD creates main menu and enables UI control
 */
UCLASS()
class SPACEBATTLES_API ASpaceMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ASpaceMainMenuHUD() { }

	/** Creates and shows main menu widget and enable UI control*/
	void BeginPlay() override;

	/** Destroy main menu widget and disable UI control*/
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	TSharedPtr<class SSpaceMainMenuWidget> MainMenuWidget;

};
