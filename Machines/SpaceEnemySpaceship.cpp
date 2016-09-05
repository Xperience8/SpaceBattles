// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceEnemySpaceship.h"

#include "SpaceshipParts/SpaceMachineGunComponent.h"
#include "SpaceSpaceshipMovementComponent.h"

#include "SpaceSpacestation.h"

#include "SpacePlayerSpaceship.h"

#include "../SpaceBattlesGameMode.h"

ASpaceEnemySpaceship::ASpaceEnemySpaceship() : TimeToThink(0.5f), TimeAccumulator(0.f), TargetLocation(0.f, 0.f, 0.f), bCollisionAvoidance(false)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	
}

void ASpaceEnemySpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TimeAccumulator += DeltaTime;
	if (TimeAccumulator >= TimeToThink)
	{
		TimeAccumulator -= TimeToThink;
		
		Think();
	}

	MoveTowardTarget();
}

void ASpaceEnemySpaceship::OnDeath()
{
	Super::OnDeath();

	auto Owner = static_cast<ASpaceSpacestation*>(GetOwner());
	if (Owner)
	{
		Owner->RemoveDefender();
	}

	static_cast<ASpaceBattlesGameMode*>(GetWorld()->GetAuthGameMode())->SpawnPickup(GetActorLocation());
}



void ASpaceEnemySpaceship::Think()
{
	CheckForFutureCollision();

	TActorIterator<ASpacePlayerSpaceship> PlayerIt(GetWorld());
	if (PlayerIt && !bCollisionAvoidance)
	{
		TargetLocation = PlayerIt->GetActorLocation();

		FVector DirToPlayer = (PlayerIt->GetActorLocation() - GetActorLocation()).GetUnsafeNormal();
		
		float DotProduct = FVector::DotProduct(GetActorForwardVector(), DirToPlayer);
		float Distance = FVector::Dist(GetActorLocation(), PlayerIt->GetActorLocation());
		if (DotProduct > 0.95f && Distance < 2500.f)
		{
			MachineGunComponent->StartShooting();
		}
		else
		{
			MachineGunComponent->StopShooting();
		}
	}

	const float Epsylon = 500.f;
	if (FVector::Dist(TargetLocation, GetActorLocation()) < Epsylon)
	{
		bCollisionAvoidance = false;
	}
}

void ASpaceEnemySpaceship::MoveTowardTarget()
{
	FVector DirectionToTarget = (TargetLocation - GetActorLocation()).GetUnsafeNormal();

	FRotator CurrentRotation = GetActorRotation();
	FRotator DesiredRotation = DirectionToTarget.Rotation();

	float DeltaYaw = DesiredRotation.Yaw - CurrentRotation.Yaw;
	if (FMath::Abs(DeltaYaw) > 180.f)
	{
		DeltaYaw *= -1.f;
	}

	float DeltaPitch = DesiredRotation.Pitch - CurrentRotation.Pitch;
	if (FMath::Abs(DeltaPitch) > 180.f)
	{
		DeltaPitch *= -1.f;
	}

	float RightSteering = FMath::Clamp(DeltaYaw, -1.f, 1.f);
	float UpSteering = FMath::Clamp(DeltaPitch, -1.f, 1.f);

	// If any steering is less then this, then current course is considered as ideal
	const float Epsylon = 0.5f;

	MovementComponent->SteerRight(FMath::Abs(RightSteering) < Epsylon ? 0.f : RightSteering);
	MovementComponent->SteerUp(FMath::Abs(UpSteering) < Epsylon ? 0.f : UpSteering);
}

void ASpaceEnemySpaceship::CheckForFutureCollision()
{
	FHitResult Hit;
	FVector LineStart = GetActorLocation() + GetActorForwardVector() * 100.f;
	FVector LineEnd = LineStart + GetActorForwardVector() * 3500.f;
	if (GetWorld()->LineTraceSingleByObjectType(Hit, LineStart, LineEnd, FCollisionObjectQueryParams()))
	{
		ECollisionChannel CollisionChannel = Hit.GetComponent()->GetCollisionObjectType();
		if (CollisionChannel == ECollisionChannel::ECC_WorldStatic || CollisionChannel == ECC_Barrier)
		{
			DealWithStaticCollision(Hit.Location, Hit.GetActor(), Hit.GetComponent());
		}
	}

	DealWithDynamicCollision();
}

void ASpaceEnemySpaceship::DealWithStaticCollision(FVector HitLocation, AActor *CollisionCandidate, UPrimitiveComponent *CollisionCandidateComponent)
{
	FVector DirectionFromCenterToHit = (HitLocation - CollisionCandidate->GetActorLocation()).GetUnsafeNormal();
	
	// It is used to determine in which direction should spaceship move to avoid collision
	FRotator DeterminantAngle = DirectionFromCenterToHit.Rotation();

	// Shift angle from 0 => 180 to -90 => 90
	if (FMath::Abs(DeterminantAngle.Pitch) > 90.f)
	{
		DeterminantAngle.Pitch = 90.f - DeterminantAngle.Pitch;
	}
	if (FMath::Abs(DeterminantAngle.Yaw) > 90.f)
	{
		DeterminantAngle.Yaw = 90.f - DeterminantAngle.Yaw;
	}

	// How far away should spaceship go to avoid collision
	float AvoidanceDistance = CollisionCandidateComponent->Bounds.SphereRadius + 300.f;

	// Avoid collision by picking the smallest direction
	// Spaceship can avoid collision only in one direction, therefore we choosing the best one
	if (FMath::Abs(45 - FMath::Abs(DeterminantAngle.Pitch)) < FMath::Abs(45 - FMath::Abs(DeterminantAngle.Yaw)))
	{
		if (DeterminantAngle.Pitch < 0.f)
		{
			AvoidanceDistance *= -1.f;
		}

		TargetLocation = CollisionCandidate->GetActorLocation() + GetActorUpVector() * AvoidanceDistance;
	}
	else
	{
		if (DeterminantAngle.Yaw < 0.f)
		{
			AvoidanceDistance *= -1.f;
		}

		TargetLocation = CollisionCandidate->GetActorLocation() + GetActorRightVector() * AvoidanceDistance;
	}

	bCollisionAvoidance = true;
}

void ASpaceEnemySpaceship::DealWithDynamicCollision()
{
	// Compute all directions from possible future collision
	// to get the best route out of a future collision
	FVector DirToNewTarget = GetActorForwardVector();
	for (TActorIterator<ASpaceEnemySpaceship> SpaceshipIt(GetWorld()); SpaceshipIt; ++SpaceshipIt)
	{
		if (*SpaceshipIt == this)
		{
			continue;
		}

		FVector OffsetFromSpaceship = GetActorLocation() - SpaceshipIt->GetActorLocation();
		if (OffsetFromSpaceship.Size() < 500.f)
		{
			DirToNewTarget += OffsetFromSpaceship.GetUnsafeNormal();
			DirToNewTarget.Normalize();
		}
	}

	TActorIterator<ASpacePlayerSpaceship> PlayerIt(GetWorld());
	if (PlayerIt)
	{
		FVector OffsetFromSpaceship = GetActorLocation() - PlayerIt->GetActorLocation();
		if (OffsetFromSpaceship.Size() < 500.f)
		{
			DirToNewTarget += OffsetFromSpaceship.GetUnsafeNormal();
			DirToNewTarget.Normalize();
		}
	}

	if (DirToNewTarget != GetActorForwardVector())
	{
		TargetLocation = GetActorLocation() + DirToNewTarget * 1250.f;
		bCollisionAvoidance = true;
	}
}
