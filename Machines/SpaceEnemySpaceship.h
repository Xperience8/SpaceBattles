// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "Machines/SpaceSpaceship.h"
#include "SpaceEnemySpaceship.generated.h"

/**
 * ASpaceEnemySpaceship is AI bot that controls spaceship
 * It can avoid static collision(planets) and dynamic collision(other spaceships)
 * It is connected with spacestation, which is it protecting
 * It can shoot on player when player is in the range
 */
UCLASS()
class SPACEBATTLES_API ASpaceEnemySpaceship : public ASpaceSpaceship
{
	GENERATED_BODY()
	
public:
	ASpaceEnemySpaceship();

	/** Move toward target and if enough time has passed, perfom think operation*/
	virtual void Tick(float DeltaTime) override;

private:
	/** Tell owner, that you are dead and spawn pickup*/
	virtual void OnDeath() override;

	/** 
	 * Check for possible future collisions and try to avoid them
	 * If there are not any collision and player is in range, shoot him
	 */
	void Think();

	/** Move toward target by rotating spaceship*/
	void MoveTowardTarget();

	/** Check if there is any possible future collision either static other dynamic one*/
	void CheckForFutureCollision();

	/** Compute new target to avoid static collision*/
	void DealWithStaticCollision(FVector HitLocation, AActor *CollisionCandidate, UPrimitiveComponent *CollisionCandidateComponent);
	
	/** Compute new target to avoid dynamic collision*/
	void DealWithDynamicCollision();

	/** How many seconds should passed until Think is called*/
	UPROPERTY(EditAnywhere)
	float TimeToThink;

	/** Location where is spaceship headed*/
	FVector TargetLocation;

	float TimeAccumulator;

	/** It is true when spaceship is avoiding any collision*/
	bool bCollisionAvoidance;
};
