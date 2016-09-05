// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceBarrierPickup.h"

#include "../Machines/SpacePlayerSpaceship.h"

void ASpaceBarrierPickup::NotifyActorBeginOverlap(AActor *OtherActor)
{
	static_cast<ASpacePlayerSpaceship*>(OtherActor)->AddBarrier(BarrierDuration);
	
	Super::NotifyActorBeginOverlap(OtherActor);
}



