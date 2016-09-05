// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceBulletProjectile.h"

ASpaceBulletProjectile::ASpaceBulletProjectile() : Lifespan(3.f)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASpaceBulletProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(Lifespan);
}

void ASpaceBulletProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector Location = GetActorLocation();
	Location += GetActorForwardVector() * Speed * DeltaSeconds;
	SetActorLocation(Location, true);
}

