// Copyright 2015 Patrick Jurasek. All Rights Reserved..

#pragma once

#include "GameFramework/Actor.h"
#include "SpacePickup.generated.h"

/**
 * SpacePickup is a base abstract class that can be picked up only once by player
 */
UCLASS(abstract)
class SPACEBATTLES_API ASpacePickup : public AActor
{
	GENERATED_BODY()

public:
	ASpacePickup();

	/**
	 * Add some boost effect to player and destroy yourself 
	 * This method should be overriden by every type of pickup
	 */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *MeshComponent;

	UPROPERTY(EditAnywhere)
	USoundWave *PickupSound;
};
