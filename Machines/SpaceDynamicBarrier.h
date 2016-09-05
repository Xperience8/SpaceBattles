// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "Machines/SpaceBarrier.h"
#include "SpaceDynamicBarrier.generated.h"

/**
 * DynamicSpaceBarrier protects its owner by destroying everything what it hits(except planets, sun and pickups)
 * It will follow its owner, therefore it is dynamic
 */
UCLASS()
class SPACEBATTLES_API ASpaceDynamicBarrier : public ASpaceBarrier
{
	GENERATED_BODY()

	ASpaceDynamicBarrier();

	/** Remove owner from collision tests*/
	virtual void BeginPlay() override;

	/** Sets barrier position to center of actor who it is protecting*/
	virtual void Tick(float DeltaSeconds) override;
	
	
};
