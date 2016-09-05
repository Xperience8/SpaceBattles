// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "SpaceRocketGunComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEBATTLES_API USpaceRocketGunComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USpaceRocketGunComponent();

	/** If there is target and enough rockets, two rockets will be fired toward him*/
	void Shoot();

	void AddRockets(int32 NumRocketsToAdd)
	{
		RocketsLeft += NumRocketsToAdd;
		if (RocketsLeft > MaxRockets)
		{
			RocketsLeft = MaxRockets;
		}
	}

	int32 GetNumRockets() const
	{
		return RocketsLeft;
	}
		
private:
	/** Rocket which will be spawned at shooting event*/
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASpaceRocketProjectile> RocketTemplate;

	UPROPERTY(EditAnywhere)
	USoundWave *ShootingSound;

	UPROPERTY(EditAnywhere)
	int32 MaxRockets;

	UPROPERTY(EditAnywhere)
	int32 RocketsLeft;
};
