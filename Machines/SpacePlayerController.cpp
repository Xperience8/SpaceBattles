// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpacePlayerController.h"


void ASpacePlayerController::BeginInactiveState()
{
	Super::BeginInactiveState();

	GetWorld()->GetAuthGameMode()->RestartPlayer(this);
}

