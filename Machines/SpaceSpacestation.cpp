// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceSpacestation.h"

#include "SpaceBarrier.h"
#include "SpaceSpaceship.h"

#include "../Environment/SpacePlanet.h"

// Sets default values
ASpaceSpacestation::ASpaceSpacestation() :  HealthPoints(10000), DelayBetweenSpawns(2.f), NumDefendersToSpawn(0), DefendingPlanet(nullptr), Barrier(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_Destructible);
	MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	MeshComponent->SetCollisionResponseToChannel(ECC_Pickup, ECollisionResponse::ECR_Ignore);
	MeshComponent->SetNotifyRigidBodyCollision(true);
	MeshComponent->bGenerateOverlapEvents = false;

	ExplosionParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("Explosion");
	ExplosionParticleSystemComponent->AttachTo(RootComponent);
	ExplosionParticleSystemComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ExplosionParticleSystemComponent->bAutoActivate = false;

	DetectionSphereComponent = CreateDefaultSubobject<USphereComponent>("Detection");
	DetectionSphereComponent->AttachTo(RootComponent);
	DetectionSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DetectionSphereComponent->SetCollisionObjectType(ECC_Boundary);
	DetectionSphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	DetectionSphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	DetectionSphereComponent->bGenerateOverlapEvents = true;
}

void ASpaceSpacestation::BeginPlay()
{
	Super::BeginPlay();

	// Spawn barrier that protects space station until all defenders are destroyed
	if (NumDefenders > 0)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;

		Barrier = GetWorld()->SpawnActor<ASpaceBarrier>(BarrierTemplate, GetActorLocation(), GetActorRotation(), SpawnParameters);
		Barrier->SetActorScale3D(FVector(25.f, 25.f, 25.f) * GetActorScale3D());
	}
}

void ASpaceSpacestation::NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult &Hit)
{
	Other->TakeDamage(INSTANT_KILL_DAMAGE, FDamageEvent(), nullptr, this);
}

void ASpaceSpacestation::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (NumDefenders > 0)
	{
		NumDefendersToSpawn = NumDefenders;

		GetWorld()->GetTimerManager().SetTimer(SpawnHandle, this, &ASpaceSpacestation::SpawnDefender, DelayBetweenSpawns, true, 0.f);
	}
}

void ASpaceSpacestation::NotifyActorEndOverlap(AActor * OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	// Remove all spaceship which were spawned with this spacestation
	UWorld *World = GetWorld();
	for (TActorIterator<ASpaceSpaceship> SpaceshipIt(World); SpaceshipIt; ++SpaceshipIt)
	{
		if (SpaceshipIt->GetOwner() == this)
		{
			World->DestroyActor(*SpaceshipIt, true);
		}
	}

	NumDefendersToSpawn = NumDefenders;

	GetWorld()->GetTimerManager().ClearTimer(SpawnHandle);
}


float ASpaceSpacestation::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (HealthPoints > 0)
	{
		HealthPoints -= DamageAmount == INSTANT_KILL_DAMAGE ? HealthPoints : DamageAmount;
		if (HealthPoints <= 0)
		{
			MeshComponent->SetHiddenInGame(true);
			MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			ExplosionParticleSystemComponent->Activate();

			UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());

			SetLifeSpan(3.f);

			if (DefendingPlanet)
			{
				DefendingPlanet->RemoveDefender();
			}
		}
	}
	return DamageAmount;
}

void ASpaceSpacestation::RemoveDefender()
{
	if (--NumDefenders <= 0 && Barrier)
	{
		Barrier->Destroy();
	}
}

void ASpaceSpacestation::SpawnDefender()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;

	FVector DefenderLocation = GetActorLocation() + GetActorForwardVector() * 1000.f;
	FRotator DefenderRotation = GetActorRotation();

	GetWorld()->SpawnActor<ASpaceSpaceship>(SpaceshipTemplate, DefenderLocation, DefenderRotation, SpawnParameters);

	--NumDefendersToSpawn;
	if (NumDefendersToSpawn <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnHandle);
	}
}
