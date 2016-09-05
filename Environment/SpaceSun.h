// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "SpaceSun.generated.h"

/**
 * SpaceSun is an actor that can be spawned in to the world
 * It can not move only rotates around origin
 * Everything is on hit destroyed
 */
UCLASS()
class SPACEBATTLES_API ASpaceSun : public AActor
{
	GENERATED_BODY()

public:
	ASpaceSun();

	/** Sun can not be destroyed, but everything what it hits is destroyed*/
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *MeshComponent;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *SunWaveParticleSystemComponent;

	/** Constantly rotates sun*/
	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent *RotatingMovementComponent;
};
