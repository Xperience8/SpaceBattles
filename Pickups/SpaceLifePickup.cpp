// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceLifePickup.h"

#include "../Machines/SpacePlayerSpaceship.h"

void ASpaceLifePickup::NotifyActorBeginOverlap(AActor *OtherActor)
{
	static_cast<ASpacePlayerSpaceship*>(OtherActor)->AddHealthPoints(HealthPoints);

	Super::NotifyActorBeginOverlap(OtherActor);
}





