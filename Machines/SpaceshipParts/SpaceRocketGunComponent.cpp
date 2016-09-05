// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceRocketGunComponent.h"

#include "../SpaceSpaceship.h"
#include "../Projectiles/SpaceRocketProjectile.h"

// Sets default values for this component's properties
USpaceRocketGunComponent::USpaceRocketGunComponent() : MaxRockets(5), RocketsLeft(5)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = false;
}


void USpaceRocketGunComponent::Shoot()
{
	if (RocketsLeft <= 0)
	{
		return;
	}

	AActor *Owner = GetOwner();
	FVector SweepStart = Owner->GetActorLocation() + Owner->GetActorForwardVector() * 500.f;
	FVector SweepEnd = SweepStart + Owner->GetActorForwardVector() * 10000.f;

	FHitResult Hit;
	if (GetWorld()->SweepSingleByObjectType(Hit, SweepStart, SweepEnd, FQuat(0.f, 0.f, 0.f, 1.f), FCollisionObjectQueryParams(), FCollisionShape::MakeBox(FVector(250.f, 250.f, 250.f))))
	{
		AActor *Target = Hit.GetActor();

		auto Owner = static_cast<ASpaceSpaceship*>(GetOwner());
		auto MeshComponent = Owner->GetMeshComponent();

		FVector LeftCannonLocation = MeshComponent->GetSocketLocation("LeftCannon");
		FVector RightCannonLocation = MeshComponent->GetSocketLocation("RightCannon");

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = Owner;

		auto LeftRocket = GetWorld()->SpawnActor<ASpaceRocketProjectile>(RocketTemplate, LeftCannonLocation, Owner->GetActorRotation(), SpawnParameters);
		LeftRocket->SetTarget(Target, FVector(0.f, 0.f, 5.f));

		auto RightRocket = GetWorld()->SpawnActor<ASpaceRocketProjectile>(RocketTemplate, RightCannonLocation, Owner->GetActorRotation(), SpawnParameters);
		RightRocket->SetTarget(Target, FVector(0.f, 0.f, -5.f));

		UGameplayStatics::PlaySoundAtLocation(this, ShootingSound, 0.5f * (LeftCannonLocation - RightCannonLocation) + LeftCannonLocation);

		--RocketsLeft;
	}
}
