// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceRocketPickup.h"

#include "../Machines/SpacePlayerSpaceship.h"
#include "../Machines/SpaceshipParts/SpaceRocketGunComponent.h"

void ASpaceRocketPickup::NotifyActorBeginOverlap(AActor *OtherActor)
{
	static_cast<ASpacePlayerSpaceship*>(OtherActor)->GetRocketGunComponent()->AddRockets(NumRockets);

	Super::NotifyActorBeginOverlap(OtherActor);
}




