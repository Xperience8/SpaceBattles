// Copyright 2015 Patrick Jurasek. All Rights Reserved..

#pragma once

#include "Pickups/SpacePickup.h"
#include "SpaceRocketPickup.generated.h"

/**
* SpaceRocketPickup is an actor that can be spawned in to the world
* It adds rockets(as ammunition) to player spaceship(which can fire them)
*/
UCLASS()
class SPACEBATTLES_API ASpaceRocketPickup : public ASpacePickup
{
	GENERATED_BODY()

public:
	ASpaceRocketPickup() : NumRockets(3) { }

	/** Rockets are added to player spaceship*/
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:

	/** How many rockets will be added to player*/
	UPROPERTY(EditAnywhere)
	int32 NumRockets;
};
