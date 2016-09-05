// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceSpaceship.h"

#include "SpaceshipParts/SpaceMachineGunComponent.h"
#include "SpaceSpaceshipMovementComponent.h"

#include "Projectiles/SpaceProjectile.h"

ASpaceSpaceship::ASpaceSpaceship() : MaxHealthPoints(1000), HealthPoints(1000)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetCollisionObjectType(ECC_Spaceship);
	MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	MeshComponent->SetNotifyRigidBodyCollision(true);
	
	ExplosionParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("Explosion");
	ExplosionParticleSystemComponent->AttachTo(RootComponent);
	ExplosionParticleSystemComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ExplosionParticleSystemComponent->bAutoActivate = false;

	EngineAudioComponent = CreateDefaultSubobject<UAudioComponent>("EngineSound");
	EngineAudioComponent->AttachTo(RootComponent);

	MachineGunAudioComponent = CreateDefaultSubobject<UAudioComponent>("MachineGunSound");
	MachineGunAudioComponent->AttachTo(RootComponent);
	MachineGunAudioComponent->bAutoActivate = false;

	MovementComponent = CreateDefaultSubobject<USpaceSpaceshipMovementComponent>("SpaceshipMovement");
	MovementComponent->UpdatedComponent = RootComponent;
	MovementComponent->SetEngineAudioComponent(EngineAudioComponent);

	MachineGunComponent = CreateDefaultSubobject<USpaceMachineGunComponent>("MachineGun");
	MachineGunComponent->SetMachineGunAudioComponent(MachineGunAudioComponent);
}

void ASpaceSpaceship::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	// Turn off audio
	MovementComponent->BlockMovement();
	MachineGunComponent->StopShooting();
}


void ASpaceSpaceship::NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult &Hit)
{
	Other->TakeDamage(INSTANT_KILL_DAMAGE, FDamageEvent(), nullptr, this);
}

float ASpaceSpaceship::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (HealthPoints > 0)
	{
		HealthPoints -= DamageAmount == INSTANT_KILL_DAMAGE ? HealthPoints : DamageAmount;
		if (HealthPoints <= 0)
		{
			OnDeath();
		}
	}
	return DamageAmount;
}

void ASpaceSpaceship::IgnoreProjectile(ASpaceProjectile * Projectile)
{
	Projectile->IgnoreActorWhenMoving(this);
	MeshComponent->IgnoreActorWhenMoving(Projectile, true);
}

void ASpaceSpaceship::OnDeath()
{
	MeshComponent->SetHiddenInGame(true);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MovementComponent->BlockMovement();
	MachineGunComponent->StopShooting();

	ExplosionParticleSystemComponent->Activate();
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());

	SetLifeSpan(3.f);
}


