// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceSpaceshipMovementComponent.h"

USpaceSpaceshipMovementComponent::USpaceSpaceshipMovementComponent() : bBlockMovement(false), AccelerationRate(500.f), CurrentSpeed(500.f), CurrentAcceleration(0.f), NormalSpeed(500.f), BoostedSpeed(1000.f), SteeringRate(45.f), EngineTimeToOverload(8.f), EngineCoolingRate(4.f), EngineAudioComponent(nullptr), EngineTemperature(0.f)
{
	
}

void USpaceSpaceshipMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	check(EngineAudioComponent);
	EngineAudioComponent->Play();
	CurrentSpeed = NormalSpeed;
}

void USpaceSpaceshipMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (ShouldSkipUpdate(DeltaTime) || bBlockMovement || !UpdatedComponent || !PawnOwner)
	{
		return;
	}

	// Try to accelerate/decelerate and move forward 
	CurrentSpeed = FMath::Clamp(CurrentSpeed + CurrentAcceleration * DeltaTime, NormalSpeed, BoostedSpeed);
	FVector MovementVector = UpdatedComponent->GetForwardVector() * DeltaTime * CurrentSpeed;

	FHitResult HitResult;
	SafeMoveUpdatedComponent(MovementVector, UpdatedComponent->GetComponentRotation(), true, HitResult);

	// Try to heat or chill engine and check whether engine temperature is normal
	EngineTemperature += CurrentAcceleration > 0.f ? DeltaTime : -DeltaTime * EngineCoolingRate;
	EngineTemperature = FMath::Clamp(EngineTemperature, 0.28f * EngineTimeToOverload, EngineTimeToOverload);
	if (EngineTemperature == EngineTimeToOverload)
	{
		GetOwner()->TakeDamage(INSTANT_KILL_DAMAGE, FDamageEvent(), nullptr, GetOwner());
	}

	EngineAudioComponent->SetFloatParameter("RPM", GetEngineRpmFactor() * MAX_ENGINE_RPM);

	// Perform steering up or down, left or right
	if (!CurrentSteering.IsNearlyZero())
	{
		FRotator CurrentRotation = UpdatedComponent->GetComponentRotation();
		CurrentRotation.Yaw = FMath::FInterpTo(CurrentRotation.Yaw, CurrentRotation.Yaw + CurrentSteering.Yaw, DeltaTime, 1.f);
		CurrentRotation.Pitch = FMath::FInterpTo(CurrentRotation.Pitch, CurrentRotation.Pitch + CurrentSteering.Pitch, DeltaTime, 1.f);
		CurrentRotation.Roll = FMath::FInterpTo(CurrentRotation.Roll, CurrentRotation.Roll + CurrentSteering.Roll, DeltaTime, 2.f);
		
		CurrentRotation.Pitch = FMath::ClampAngle(CurrentRotation.Pitch, -85.f, 85.f);
		CurrentRotation.Roll = FMath::ClampAngle(CurrentRotation.Roll, -90.f, 90.f);
		UpdatedComponent->SetRelativeRotation(CurrentRotation);
	}
}

