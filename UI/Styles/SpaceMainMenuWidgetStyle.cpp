// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceMainMenuWidgetStyle.h"


FSpaceMainMenuStyle::FSpaceMainMenuStyle()
{
}

FSpaceMainMenuStyle::~FSpaceMainMenuStyle()
{
}

const FName FSpaceMainMenuStyle::TypeName(TEXT("FSpaceMainMenuStyle"));

const FSpaceMainMenuStyle& FSpaceMainMenuStyle::GetDefault()
{
	static FSpaceMainMenuStyle Default;
	return Default;
}

void FSpaceMainMenuStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

