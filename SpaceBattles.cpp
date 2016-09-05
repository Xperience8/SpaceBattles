// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "UI/Styles/SpaceStyles.h"

class FSpaceGameModuleImpl : public FDefaultGameModuleImpl
{
public:
	void StartupModule() override
	{
		FSpaceStyles::Initialize();
	}
	void ShutdownModule() override
	{
		FSpaceStyles::Destroy();
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE( FSpaceGameModuleImpl, SpaceBattles, "SpaceBattles" );
