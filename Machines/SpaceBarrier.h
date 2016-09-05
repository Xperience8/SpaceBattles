// Copyright 2015 Patrick Jurasek. All Rights Reserved..

#pragma once

#include "GameFramework/Actor.h"
#include "SpaceBarrier.generated.h"

/**
 * SpaceBarrier protects its owner by destroying everything what it hits(except planets, sun and pickups)
 */
UCLASS()
class SPACEBATTLES_API ASpaceBarrier : public AActor
{
	GENERATED_BODY()

public:
	ASpaceBarrier();

	/** Destroy hit actor*/
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	/** Barrier wouldn't collide with this actor*/
	void IgnoreActorWhenMoving(AActor *Actor)
	{
		MeshComponent->IgnoreActorWhenMoving(Actor, true);
	}

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *MeshComponent;
};
