// Copyright 2015 Patrick Jurasek. All Rights Reserved..

#pragma once

#include "Machines/SpaceSpaceship.h"
#include "SpacePlayerSpaceship.generated.h"

/**
 * SpacePlayerSpaceship is controlled by player
 * It has two types of weapons -> RocketGun and MachineGun
 * It can pick up pickups which add temporary features(like barrier, health or rockets) 
 */
UCLASS()
class SPACEBATTLES_API ASpacePlayerSpaceship : public ASpaceSpaceship
{
	GENERATED_BODY()

public:
	ASpacePlayerSpaceship();

	/** Called to bind functionality to input*/
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/** Turn off collision with this projectile*/
	virtual void IgnoreProjectile(class ASpaceProjectile *Projectile) override;

	/** Some portion of health is restored*/
	void AddHealthPoints(int32 HealthPointsToAdd)
	{
		HealthPoints += HealthPointsToAdd;
		if (HealthPoints > MaxHealthPoints)
		{
			HealthPoints = MaxHealthPoints;
		}
	}

	/** Temporary barrier around spaceship is created or if it has already been created time of previously added barrier would have restored*/
	void AddBarrier(float BarrierLifeSpan);

	/** Returns how many HP has player in range 0.f(Dead) to 1.f(Full HP)*/
	float GetLifeFactor() const
	{
		return static_cast<float>(HealthPoints) / static_cast<float>(MaxHealthPoints);
	}

	/** Can not be null*/
	class USpaceRocketGunComponent *GetRocketGunComponent() const
	{
		return RocketGunComponent;
	}

private:
	virtual void OnDeath() override;

	void ExitGameRequest();

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent *SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent *CameraComponent;

	UPROPERTY(VisibleAnywhere)
	class USpaceRocketGunComponent *RocketGunComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASpaceDynamicBarrier> BarrierTemplate;

	UPROPERTY()
	class ASpaceBarrier *Barrier;

};
