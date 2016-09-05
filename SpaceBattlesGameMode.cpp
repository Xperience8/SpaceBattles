// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceBattlesGameMode.h"

#include "UI/SpaceGameHUD.h"
#include "Machines/SpacePlayerSpaceship.h"
#include "Machines/SpacePlayerController.h"

#include "Pickups/SpaceLifePickup.h"
#include "Pickups/SpaceRocketPickup.h"
#include "Pickups/SpaceBarrierPickup.h"

ASpaceBattlesGameMode::ASpaceBattlesGameMode()
{
	ConstructorHelpers::FClassFinder<APawn> PlayerPawn(TEXT("/Game/Blueprints/Spaceships/PlayerSpaceshipTemplate"));

	HUDClass = ASpaceGameHUD::StaticClass();
	DefaultPawnClass = PlayerPawn.Class;
	PlayerControllerClass = ASpacePlayerController::StaticClass();
	
	ConstructorHelpers::FClassFinder<ASpaceLifePickup> LifePickup(TEXT("/Game/Blueprints/Pickups/LifePickupTemplate"));
	ConstructorHelpers::FClassFinder<ASpaceRocketPickup> RocketPickup(TEXT("/Game/Blueprints/Pickups/RocketPickupTemplate"));
	ConstructorHelpers::FClassFinder<ASpaceBarrierPickup> BarrierPickup(TEXT("/Game/Blueprints/Pickups/BarrierPickupTemplate"));
	PickupTemplates.Add(LifePickup.Class);
	PickupTemplates.Add(RocketPickup.Class);
	PickupTemplates.Add(BarrierPickup.Class);
}

void ASpaceBattlesGameMode::SpawnPickup(FVector SpawnLocation)
{
	int32 PickupType = FMath::RandRange(0, PickupTemplates.Num() - 1);

	GetWorld()->SpawnActor<ASpacePickup>(PickupTemplates[PickupType], SpawnLocation, FRotator(0.f, 0.f, 0.f));
}