// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
/**
*
*/
class SPACEBATTLES_API FSpaceStyles
{
public:

	static void Initialize();
	static void Destroy();

	static TSharedPtr<FSlateStyleSet> &Get() { return Instance; }
private:
	static TSharedPtr<FSlateStyleSet> Instance;
	static FName Name;
	static FString Directory;
};
