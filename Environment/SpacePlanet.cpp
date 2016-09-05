// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpacePlanet.h"

#include "../SpaceGameInstance.h"
#include "../Machines/SpaceSpacestation.h"

ASpacePlanet::ASpacePlanet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	MeshComponent->SetCollisionResponseToChannel(ECC_Pickup, ECollisionResponse::ECR_Ignore);
	MeshComponent->SetNotifyRigidBodyCollision(true);
	MeshComponent->bGenerateOverlapEvents = false;

	CompletedParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("CompletedWave");
	CompletedParticleSystemComponent->AttachTo(RootComponent);
	CompletedParticleSystemComponent->bAutoActivate = false;
	CompletedParticleSystemComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("RotatingComponent");
	RotatingMovementComponent->UpdatedComponent = RootComponent;
	RotatingMovementComponent->bUpdateOnlyIfRendered = true;
	RotatingMovementComponent->RotationRate.Yaw = 2.f;
}

void ASpacePlanet::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Check whether this planet is extempted
	// If it is, destroy every spacestation which is protecting it
	if (static_cast<USpaceGameInstance*>(GetGameInstance())->IsPlanetExtempted(GetName()))
	{
		for (TActorIterator<ASpaceSpacestation> SpacestationIt(GetWorld()); SpacestationIt; ++SpacestationIt)
		{
			if (SpacestationIt->GetDefendingPlanet() == this)
			{
				SpacestationIt->Destroy();
			}
		}

		NumDefenders = 0;
	}

	// If there aren't any defenders left, activate special effect, which mark this planet as free
	if (NumDefenders == 0)
	{
		CompletedParticleSystemComponent->Activate();
	}
}

void ASpacePlanet::NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit)
{
	Other->TakeDamage(INSTANT_KILL_DAMAGE, FDamageEvent(), nullptr, this);
}

void ASpacePlanet::RemoveDefender()
{
	if (--NumDefenders == 0)
	{
		CompletedParticleSystemComponent->Activate();

		// Bookmark this planet as extempted
		static_cast<USpaceGameInstance*>(GetGameInstance())->AddExtemptedPlanet(GetName());
	}
}

