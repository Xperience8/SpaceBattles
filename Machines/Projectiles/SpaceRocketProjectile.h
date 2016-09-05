// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "Machines/Projectiles/SpaceProjectile.h"
#include "SpaceRocketProjectile.generated.h"

/**
 * SpaceRocketProjectile can move in any direction in constant speed
 * It will follow its target until it hits him(or it will be destroyed by hitting something else)
 * It's main job is to make big damage
 */
UCLASS()
class SPACEBATTLES_API ASpaceRocketProjectile : public ASpaceProjectile
{
	GENERATED_BODY()

public:
	ASpaceRocketProjectile();

	/** Moves toward target*/
	virtual void Tick(float DeltaSeconds) override;

	/**
	 * Sets target that will be followed by this projectile
	 * and offset from targets pivot point(where rocket hits target),
	 * therefore multiple rockets can be fired at the same time
	 */
	void SetTarget(AActor *NewTarget, FVector NewOffsetFromTarget)
	{
		Target = NewTarget;
		OffsetFromTarget = NewOffsetFromTarget;
	}
private:
	/** Actor that is followed by this rocket*/
	AActor *Target;

	/** Offset from targets pivot point, where rocket will hit target*/
	FVector OffsetFromTarget;
};
