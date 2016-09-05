// Copyright 2015 Patrick Jurasek. All Rights Reserved..

#pragma once

#include "Pickups/SpacePickup.h"
#include "SpaceBarrierPickup.generated.h"

/**
 * SpaceBarrierPickup is and actor that can be spawned in to the world
 * It creates temporary barrier around player spaceship
 */
UCLASS()
class SPACEBATTLES_API ASpaceBarrierPickup : public ASpacePickup
{
	GENERATED_BODY()

public:
	ASpaceBarrierPickup() : BarrierDuration(8.f) { }

	/** Temporary barrier is created around player*/
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:

	/** How many seconds will be barrier active*/
	UPROPERTY(EditAnywhere)
	float BarrierDuration;
};