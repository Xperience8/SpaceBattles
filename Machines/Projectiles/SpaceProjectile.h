// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "SpaceProjectile.generated.h"

/**
 * SpaceProjectile is an abstrach base class
 * It's main job is to make damage
 */
UCLASS(abstract)
class SPACEBATTLES_API ASpaceProjectile : public AActor
{
	GENERATED_BODY()

public:
	ASpaceProjectile();

	/** Make sure that projectile doesn't hit its owner */
	virtual void BeginPlay() override;

	/** Causes damage to actor which projectile hits*/
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	/** Destroy yourself(Projectile hits something)*/
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	/** SpaceProjectile shouldn't hit selected actor(it won't collide with him)*/
	void IgnoreActorWhenMoving(AActor *Actor)
	{
		MeshComponent->IgnoreActorWhenMoving(Actor, true);
	}

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *MeshComponent;

	/** If projectile hits any actor, particle system with special effect will be activated*/
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *HitParticleSystemComponent;

	/** If projectile hits any actor, sound will be played*/
	UPROPERTY(EditAnywhere)
	USoundWave *HitSound;

	/** How fast is projectile moving*/
	UPROPERTY(EditAnywhere)
	float Speed;

	/** Damage which projectile causes*/
	UPROPERTY(EditAnywhere)
	float Damage;
};
