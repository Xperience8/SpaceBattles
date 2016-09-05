// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceMachineGunComponent.h"

#include "../SpaceSpaceship.h"
#include "../Projectiles/SpaceBulletProjectile.h"

// Sets default values for this component's properties
USpaceMachineGunComponent::USpaceMachineGunComponent() : DelayBetweenShots(0.17f), LastShotTime(-10.f), bShooting(false), ShootingSoundAudioComponent(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = true;
}

void USpaceMachineGunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bShooting)
	{
		float CurrentTime = GetWorld()->GetTimeSeconds();
		if (CurrentTime > LastShotTime + DelayBetweenShots)
		{
			LastShotTime = CurrentTime;

			auto Owner = static_cast<ASpaceSpaceship*>(GetOwner());
			auto MeshComponent = Owner->GetMeshComponent();

			FVector LeftCannonLocation = MeshComponent->GetSocketLocation("LeftCannon");
			FVector RightCannonLocation = MeshComponent->GetSocketLocation("RightCannon");

			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = GetOwner();
			GetWorld()->SpawnActor<ASpaceBulletProjectile>(BulletTemplate, LeftCannonLocation, Owner->GetActorRotation(), SpawnParameters);
			GetWorld()->SpawnActor<ASpaceBulletProjectile>(BulletTemplate, RightCannonLocation, Owner->GetActorRotation(), SpawnParameters);
		}
	}
}


