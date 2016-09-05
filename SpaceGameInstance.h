// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "Engine/GameInstance.h"
#include "SpaceGameInstance.generated.h"

/**
 * USpaceGameInstance creates and manages save system
 * It can save, load and launch game 
 */
UCLASS()
class SPACEBATTLES_API USpaceGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	/** Find out whether save game exist*/
	virtual void Init() override;

	/** 
	 * If bContinue is false and save game exists, then saved data will be destroyed
	 * If bContinue is false and save game doesn't exist, then new game will be launched
	 * If bContinue is true, game will be loaded
	 */
	void LaunchGame(bool bContinue);

	/** Add extempted planet to the list and save it to the save slot*/
	void AddExtemptedPlanet(FString PlanetName);

	/** Returns true if planet is in the list of extempted planets*/
	bool IsPlanetExtempted(FString PlanetName) const;

	/** Returns true if save game exists*/
	bool DoesGameSaveExist() const
	{
		return bSavedGameExist;
	}

private:
	const FString SaveSlot = "Autosave";
	const int32 SaveSlotIndex = 0;

	UPROPERTY()
	class USpaceSaveGame *SaveGameSystem;
	
	bool bSavedGameExist;
};
