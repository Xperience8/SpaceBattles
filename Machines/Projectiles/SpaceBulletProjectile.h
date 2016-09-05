// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "Machines/Projectiles/SpaceProjectile.h"
#include "SpaceBulletProjectile.generated.h"

/**
 * SpaceBulletProjectile has restricted lifetime
 * It can move only forward in constant speed
 * It's main job is to make small damage
 */
UCLASS()
class SPACEBATTLES_API ASpaceBulletProjectile : public ASpaceProjectile
{
	GENERATED_BODY()

public:
	ASpaceBulletProjectile();

	/** Set lifespan of this bullet*/
	virtual void BeginPlay() override;

	/** Move forward in constant speed*/
	virtual void Tick(float DeltaSeconds) override;

private:
	/**
	* Bullet is only alive for small amount of time,
	* When it won't hit anything and time will pass, it will be destroyed
	*/
	UPROPERTY(EditAnywhere)
	float Lifespan;
};
