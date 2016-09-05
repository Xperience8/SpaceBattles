// Copyright 2015 Patrick Jurasek. All Rights Reserved..

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "SpaceSpaceshipMovementComponent.generated.h"

/**
 * SpaceSpaceshipMovementComponent always moves
 * It can steer up, down, left or right
 * It can go in boosted speed for small amount of time(more rpm)
 * If level of rpm is too big, spaceship will be destroyed
 */
UCLASS()
class SPACEBATTLES_API USpaceSpaceshipMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	USpaceSpaceshipMovementComponent();

	/** Engine sound is controlled by speed*/
	void SetEngineAudioComponent(UAudioComponent *AudioComponent)
	{
		EngineAudioComponent = AudioComponent;
	}

	/** Start playing engine sound*/
	virtual void BeginPlay() override;

	/**
	 * Spaceship always goes forward
	 * It can go in boosted speed until engine will be overloaded
	 * It can steer up, down, left or right
	 */
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	/** Spaceship will accelerate until Decelerate is called or engine is overloaded*/
	void Accelerate()
	{
		CurrentAcceleration = AccelerationRate;
	}

	/** Spaceship will decelerate until Accelerate is called or spaceship reaches default speed*/
	void Decelerate()
	{
		CurrentAcceleration = -AccelerationRate;
	}

	/** Spaceship can steer up or down(negative value), only pitch is affected*/
	void SteerUp(float Axis)
	{
		CurrentSteering.Pitch = Axis * SteeringRate;
	}

	/** Spaceship can steer right or left(negative value), yaw and roll are affected*/
	void SteerRight(float Axis)
	{
		CurrentSteering.Yaw = Axis * SteeringRate;
		CurrentSteering.Roll = Axis != 0.f ? Axis * SteeringRate : -UpdatedComponent->GetComponentRotation().Roll;
	}

	/** Spaceship can not move and engine sound is turned off*/
	void BlockMovement() 
	{
		EngineAudioComponent->Stop();
		bBlockMovement = true;
	}

	/** Returns engine rpm in range 0.f to 1.f*/
	float GetEngineRpmFactor() const
	{
		return EngineTemperature / EngineTimeToOverload;
	}

private:
	const float MAX_ENGINE_RPM = 9000.f;

	/** Engine sound is dependent on spaceship moving speed*/
	UAudioComponent *EngineAudioComponent;

	/** How many seconds can spaceship go in full speed(after this time is spaceship destroyed)*/
	UPROPERTY(EditAnywhere)
	float EngineTimeToOverload;

	/** How fast is engine cooling when spaceship doesn't accelerate*/
	UPROPERTY(EditAnywhere)
	float EngineCoolingRate;

	/** If EngineTemperature hits EngineTimeToOverload spaceship will be destroyed*/
	float EngineTemperature;

	/** NormalSpeed is used when player doesn't want to accelerate*/
	UPROPERTY(EditAnywhere)
	float NormalSpeed;

	/** BoostedSpeed is used when player wants to accelerate*/
	UPROPERTY(EditAnywhere)
	float BoostedSpeed;

	/** How fast can spaceship accelerate*/
	UPROPERTY(EditAnywhere)
	float AccelerationRate;

	/** How fast can spaceship make pitch, yaw or roll rotation(roll is two times faster than pitch or yaw)*/
	UPROPERTY(EditAnywhere)
	float SteeringRate;

	float CurrentSpeed;

	float CurrentAcceleration;

	FRotator CurrentSteering;

	bool bBlockMovement;
};