// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "SpaceMachineGunComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEBATTLES_API USpaceMachineGunComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USpaceMachineGunComponent();

	/** New bullets will be spawned if enough time has passed*/
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartShooting()
	{
		if (!bShooting)
		{
			bShooting = true;
			ShootingSoundAudioComponent->Play(LastShotTime + DelayBetweenShots - GetWorld()->GetTimeSeconds());
		}
	}

	void StopShooting()
	{
		if (bShooting)
		{
			bShooting = false;
			ShootingSoundAudioComponent->Stop();
		}
	}

	/** Set audio component which will be controlled based on shooting status*/
	void SetMachineGunAudioComponent(UAudioComponent *AudioComponent)
	{
		ShootingSoundAudioComponent = AudioComponent;
	}

private:
	/** Bullet which will be spawned at shooting event*/
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASpaceBulletProjectile> BulletTemplate;
		
	UAudioComponent *ShootingSoundAudioComponent;

	/** How many seconds should pass between shots*/
	UPROPERTY(EditAnywhere)
	float DelayBetweenShots;

	float LastShotTime;

	bool bShooting;
};
