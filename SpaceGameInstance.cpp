// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceGameInstance.h"

#include "SpaceSaveGame.h"

void USpaceGameInstance::Init()
{
	Super::Init();

	SaveGameSystem = static_cast<USpaceSaveGame*>(UGameplayStatics::CreateSaveGameObject(USpaceSaveGame::StaticClass()));
	bSavedGameExist = UGameplayStatics::DoesSaveGameExist(SaveSlot, SaveSlotIndex);
}

void USpaceGameInstance::LaunchGame(bool bContinue)
{
	if (bContinue)
	{
		SaveGameSystem = static_cast<USpaceSaveGame*>(UGameplayStatics::LoadGameFromSlot(SaveSlot, SaveSlotIndex));
	}
	else
	{
		if (bSavedGameExist)
		{
			UGameplayStatics::DeleteGameInSlot(SaveSlot, SaveSlotIndex);
		}
	}

	UGameplayStatics::OpenLevel(GetWorld(), "/Game/Maps/SpaceWorld");
}

void USpaceGameInstance::AddExtemptedPlanet(FString PlanetName)
{
	SaveGameSystem->AddExtemptedPlanet(PlanetName);

	UGameplayStatics::SaveGameToSlot(SaveGameSystem, SaveSlot, SaveSlotIndex);
}

bool USpaceGameInstance::IsPlanetExtempted(FString PlanetName) const
{
	return SaveGameSystem->IsPlanetExtempted(PlanetName);
}
