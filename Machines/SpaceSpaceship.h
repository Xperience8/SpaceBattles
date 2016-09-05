// Copyright 2015 Patrick Jurasek. All Rights Reserved..

#pragma once

#include "GameFramework/Pawn.h"
#include "SpaceSpaceship.generated.h"

/**
 * SpaceSpaceship is an abstract base class that creates spaceship which can be added into the world
 * It should by override to add specific features like player or bot
 */
UCLASS(abstract)
class SPACEBATTLES_API ASpaceSpaceship : public APawn
{
	GENERATED_BODY()

public:
	ASpaceSpaceship();

	/** Turn off all sounds that spaceship is producing*/
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Spaceship kills everything what it hits*/
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	/** Spaceship can be damaged by projectile or instantly killed by hitting another object*/
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	/** Turn off collision with specific projectile*/
	virtual void IgnoreProjectile(class ASpaceProjectile *Projectile);

	/** Can not be null*/
	UStaticMeshComponent *GetMeshComponent()
	{
		return MeshComponent;
	}

protected:
	virtual void OnDeath();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *MeshComponent;

	UPROPERTY(VisibleAnywhere)
	UAudioComponent *EngineAudioComponent;

	UPROPERTY(VisibleAnywhere)
	UAudioComponent *MachineGunAudioComponent;

	UPROPERTY(VisibleAnywhere)
	class USpaceSpaceshipMovementComponent *MovementComponent;

	UPROPERTY(VisibleAnywhere)
	class USpaceMachineGunComponent *MachineGunComponent;
	
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *ExplosionParticleSystemComponent;

	UPROPERTY(EditAnywhere)
	USoundCue *ExplosionSound;

	UPROPERTY(EditAnywhere)
	int32 MaxHealthPoints;

	UPROPERTY(EditAnywhere)
	int32 HealthPoints;
};
