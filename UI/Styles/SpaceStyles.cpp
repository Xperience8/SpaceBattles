// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceStyles.h"
#include "SlateGameResources.h"

TSharedPtr<FSlateStyleSet> FSpaceStyles::Instance = nullptr;
FName FSpaceStyles::Name = "SpaceStyles";
FString FSpaceStyles::Directory = "/Game/UI/Styles";

void FSpaceStyles::Initialize()
{
	if (Instance.IsValid())
	{
		Destroy();
	}

	Instance = FSlateGameResources::New(Name, Directory, Directory);
	FSlateStyleRegistry::RegisterSlateStyle(*Instance);
}

void FSpaceStyles::Destroy()
{
	if (Instance.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*Instance);
		ensure(Instance.IsUnique());
		Instance.Reset();
	}
}