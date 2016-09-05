// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "GameFramework/PlayerController.h"
#include "SpacePlayerController.generated.h"

/**
 * SpacePlayerController restarts player when he dies
 */
UCLASS()
class SPACEBATTLES_API ASpacePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	/** Restart player*/
	virtual void BeginInactiveState() override;
	
	
	
};
