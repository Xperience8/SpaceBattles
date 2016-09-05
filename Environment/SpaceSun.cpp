// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceSun.h"

ASpaceSun::ASpaceSun()
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

	SunWaveParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("SunWave");
	SunWaveParticleSystemComponent->AttachTo(RootComponent);
	SunWaveParticleSystemComponent->bAutoActivate = true;
	SunWaveParticleSystemComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("RotatingComponent");
	RotatingMovementComponent->UpdatedComponent = RootComponent;
	RotatingMovementComponent->bUpdateOnlyIfRendered = true;
	RotatingMovementComponent->RotationRate.Yaw = 2.f;
}

void ASpaceSun::NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit)
{
	Other->TakeDamage(INSTANT_KILL_DAMAGE, FDamageEvent(), nullptr, this);
}


