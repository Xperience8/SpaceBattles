// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceRocketProjectile.h"

ASpaceRocketProjectile::ASpaceRocketProjectile() : Target(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASpaceRocketProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Rocket is destroyed and particle animation of explosion is played
	if (Speed == 0.f)
	{
		return;
	}

	// If something else destroyed our target projectile would kill yourself
	if (!Target || Target->IsPendingKillPending())
	{
		TakeDamage(INSTANT_KILL_DAMAGE, FDamageEvent(), nullptr, this);
		return;
	}

	FVector DirToTarget = ((Target->GetActorLocation() + OffsetFromTarget) - GetActorLocation()).GetUnsafeNormal();
	FVector ActorLocation = GetActorLocation();
	ActorLocation += DirToTarget * Speed * DeltaSeconds;
	SetActorLocation(ActorLocation, true);
}
