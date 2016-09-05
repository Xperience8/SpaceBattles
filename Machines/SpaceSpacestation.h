// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "SpaceSpacestation.generated.h"

/**
 * ASpaceStation can not be damaged until all defenders are destroyed
 * Defenders are spawned slowly in waves, when player enters detection sphere
 * If it is destroyed then message is send to planet, which is spacestation protecting
 */
UCLASS()
class SPACEBATTLES_API ASpaceSpacestation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceSpacestation();

	/** Spawn barrier that protects space station until all defenders are destroyed*/
	virtual void BeginPlay() override;

	/** Space station kills everything what it hits*/
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	/** Start to spawning defenders*/
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	/** Remove all defenders whichS are allive*/
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	/** Space station can be damaged by projectile or instantly killed by hitting another object*/
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	/** Can be null*/
	const class ASpacePlanet *GetDefendingPlanet() const
	{
		return DefendingPlanet;
	}

	/** Removes defender, it there are not any defenders left, barrier will be destroyed*/
	void RemoveDefender();

protected:
	/** Spawn spaceship to protect this spacestation*/
	void SpawnDefender();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *MeshComponent;

	/** If player will be detected by this sphere, then defenders will be slowly spawned*/
	UPROPERTY(VisibleAnywhere)
	USphereComponent *DetectionSphereComponent;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *ExplosionParticleSystemComponent;

	UPROPERTY(EditAnywhere)
	USoundCue *ExplosionSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASpaceBarrier> BarrierTemplate;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASpaceSpaceship> SpaceshipTemplate;
	
	UPROPERTY(EditAnywhere)
	class ASpacePlanet *DefendingPlanet;

	class ASpaceBarrier *Barrier;

	FTimerHandle SpawnHandle;

	/** How many defenders are protecting this spacestation*/
	UPROPERTY(EditAnywhere)
	int32 NumDefenders;

	/** How many seconds should passed between spawns*/
	UPROPERTY(EditAnywhere)
	float DelayBetweenSpawns;

	/** How many defenders can be spawned*/
	int32 NumDefendersToSpawn;

	UPROPERTY(EditAnywhere)
	int32 HealthPoints;
};
