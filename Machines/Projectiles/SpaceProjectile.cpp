// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceProjectile.h"

#include "../SpaceSpaceship.h"
#include "../SpaceBarrier.h"

ASpaceProjectile::ASpaceProjectile() : Speed(500.f), Damage(50.f)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetCollisionObjectType(ECC_Projectile);
	MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	MeshComponent->SetCollisionResponseToChannel(ECC_Pickup, ECollisionResponse::ECR_Ignore);
	MeshComponent->SetNotifyRigidBodyCollision(true);
	MeshComponent->bGenerateOverlapEvents = false;

	HitParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("HitParticles");
	HitParticleSystemComponent->AttachTo(RootComponent);
	HitParticleSystemComponent->bAutoActivate = false;
	HitParticleSystemComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASpaceProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Projectile can not hit its owner
	static_cast<ASpaceSpaceship*>(GetOwner())->IgnoreProjectile(this);
}

void ASpaceProjectile::NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit)
{
	Other->TakeDamage(Damage, FDamageEvent(), nullptr, this);
}

float ASpaceProjectile::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	// Quick hack to stop moving
	Speed = 0.f;
	MeshComponent->SetHiddenInGame(true);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HitParticleSystemComponent->Activate();
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());

	SetLifeSpan(3.f);

	return 0.0f;
}