// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "SpacePlanet.generated.h"

/**
 * SpacePlanet is an actor that can be spawned in to the world
 * It is static actor which can not move, only rotates around origin
 * It can not be destroyed, but it destroys everything on hit
 * It has several spacestations which protect it
 * When all spacestations are destroyed, it is marked as free
 */
UCLASS()
class SPACEBATTLES_API ASpacePlanet : public AActor
{
	GENERATED_BODY()

public:
	ASpacePlanet();

	/** 
	 * Load information whether this planet has been extempted
	 * and if it was, then destroy all defenders nearby and mark this planet as free
	 */
	virtual void PostInitializeComponents() override;

	/** Planet can not be destroyed, but everything what it hits is destroyed*/
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	/** If number of defenders drops to zero, this planet will be marked as free*/
	void RemoveDefender();

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *MeshComponent;

	/** Signalizes player whether this planet is free*/
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *CompletedParticleSystemComponent;

	/** Constantly rotates planet*/
	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent *RotatingMovementComponent;

	/** How many spacestations are defending this planet*/
	UPROPERTY(EditAnywhere)
	int32 NumDefenders;
};
