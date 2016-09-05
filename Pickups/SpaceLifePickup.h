// Copyright 2015 Patrick Jurasek. All Rights Reserved..

#pragma once

#include "Pickups/SpacePickup.h"
#include "SpaceLifePickup.generated.h"

/**
 * SpaceLifePickup is an actor that can be spawned in to the world
 * It adds health points to player
 */
UCLASS()
class SPACEBATTLES_API ASpaceLifePickup : public ASpacePickup
{
	GENERATED_BODY()

public:
	ASpaceLifePickup() : HealthPoints(1000) { }

	/** Health points are send to player spaceship, which can reject them(has full life) or take them*/
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	/** How many health points will be restored to player*/
	UPROPERTY(EditAnywhere)
	int32 HealthPoints;
};
