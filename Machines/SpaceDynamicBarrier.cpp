// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceDynamicBarrier.h"

ASpaceDynamicBarrier::ASpaceDynamicBarrier()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASpaceDynamicBarrier::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->IgnoreActorWhenMoving(GetOwner(), true);
}

void ASpaceDynamicBarrier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetOwner()->GetActorLocation(), true);
}

