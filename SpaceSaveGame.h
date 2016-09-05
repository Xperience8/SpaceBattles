// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "GameFramework/SaveGame.h"
#include "SpaceSaveGame.generated.h"

/**
 * USpaceSaveGame saves names of planets which have been extempted
 */
UCLASS()
class SPACEBATTLES_API USpaceSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	bool IsPlanetExtempted(FString PlanetName) const
	{
		for (auto &ExtemptedPlanetName : ExtemptedPlanets)
		{
			if (ExtemptedPlanetName == PlanetName)
			{
				return true;
			}
		}

		return false;
	}

	void AddExtemptedPlanet(FString PlanetName)
	{
		ExtemptedPlanets.AddUnique(PlanetName);
	}

private:
	UPROPERTY()
	TArray<FString> ExtemptedPlanets;	
};
