// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once


#include "Widgets/SCompoundWidget.h"

/**
 * SSpaceMainMenuWidget creates main menu with 2 or 3 elements with or without continue
 */
class SPACEBATTLES_API SSpaceMainMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSpaceMainMenuWidget)
	{}
	SLATE_ARGUMENT(class ASpaceMainMenuHUD*, HUD)
	SLATE_ARGUMENT(bool, bGameSaveExist)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	FReply OnContinueClick();
	FReply OnNewGameClick();
	FReply OnExitClick();

	class ASpaceMainMenuHUD *MainMenuHUD;

};
