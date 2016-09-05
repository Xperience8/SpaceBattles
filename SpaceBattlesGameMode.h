// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "GameFramework/GameMode.h"
#include "SpaceBattlesGameMode.generated.h"

/**
 * ASpaceBattlesGameMode can spawn pickups at specified locations
 */
UCLASS()
class SPACEBATTLES_API ASpaceBattlesGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ASpaceBattlesGameMode();

	/** Spawn random pickup at specified location*/
	void SpawnPickup(FVector SpawnLocation);

private:
	TArray<TSubclassOf<class ASpacePickup> > PickupTemplates;
};
