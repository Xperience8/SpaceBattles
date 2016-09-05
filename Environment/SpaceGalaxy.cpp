// Copyright 2016 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceGalaxy.h"

ASpaceGalaxy::ASpaceGalaxy() 
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GameZoneComponent = CreateDefaultSubobject<USphereComponent>("GameZone");
	RootComponent = GameZoneComponent;
	GameZoneComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GameZoneComponent->SetCollisionObjectType(ECC_Boundary);
	GameZoneComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	GameZoneComponent->SetSphereRadius(50000.f);
	GameZoneComponent->SetMobility(EComponentMobility::Static);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->AttachTo(RootComponent);
	MeshComponent->SetRelativeScale3D(FVector(10000.f, 10000.f, 10000.f));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetMobility(EComponentMobility::Static);
}

void ASpaceGalaxy::NotifyActorEndOverlap(AActor * OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
	// Kill actor, if he has not already been killed
	if (!OtherActor->IsPendingKillPending())
	{
		OtherActor->TakeDamage(INSTANT_KILL_DAMAGE, FDamageEvent(), nullptr, this);
	}
}
