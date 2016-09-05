// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpacePickup.h"

ASpacePickup::ASpacePickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionObjectType(ECC_Pickup);
	MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	MeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	MeshComponent->bGenerateOverlapEvents = true;
}

void ASpacePickup::NotifyActorBeginOverlap(AActor *OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());

	Destroy();
}


