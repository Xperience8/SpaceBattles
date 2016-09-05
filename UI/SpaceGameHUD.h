// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "GameFramework/HUD.h"
#include "SpaceGameHUD.generated.h"

/**
 * ASpaceGameHUD creates HUD that shows player
 * how many rockets, rpm and HP he has
 */
UCLASS()
class SPACEBATTLES_API ASpaceGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	ASpaceGameHUD();

	virtual void DrawHUD() override;
private:
	FCanvasIcon ScopeIcon;
	FCanvasIcon RpmMeterIcon;
	FCanvasIcon RpmPointerIcon;
	FCanvasIcon LifeMeterIcon;
	FCanvasIcon RocketIcon;
};
