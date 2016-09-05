// Copyright 2016 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "SpaceGalaxy.generated.h"

/**
 * SpaceGalaxy is a static actor, that encircles whole game world
 * SpaceGalaxy checks game world and if any spaceship left game zone, spaceship would be destroyed
 */
UCLASS()
class SPACEBATTLES_API ASpaceGalaxy : public AActor
{
	GENERATED_BODY()

public:
	ASpaceGalaxy();

	/** If any spaceship left game zone, it would be destroyed*/
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *MeshComponent;

	UPROPERTY(VisibleAnywhere)
	USphereComponent *GameZoneComponent;
};
