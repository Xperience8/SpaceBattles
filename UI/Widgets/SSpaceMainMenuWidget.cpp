// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SSpaceMainMenuWidget.h"
#include "SlateOptMacros.h"

#include "../SpaceMainMenuHUD.h"
#include "../../SpaceGameInstance.h"

#include "../Styles/SpaceStyles.h"
#include "../Styles/SpaceMainMenuWidgetStyle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSpaceMainMenuWidget::Construct(const FArguments& InArgs)
{
	MainMenuHUD = InArgs._HUD;

	auto &MainMenuStyle = FSpaceStyles::Get()->GetWidgetStyle<FSpaceMainMenuStyle>("MainMenuStyle");

	TSharedPtr<SVerticalBox> VerticalBox;

	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(EHorizontalAlignment::HAlign_Fill)
		.VAlign(EVerticalAlignment::VAlign_Fill)
		[
			SNew(SImage)
			.Image(&MainMenuStyle.BackgroundImage)
		]
		+ SOverlay::Slot()
		.HAlign(EHorizontalAlignment::HAlign_Right)
		.VAlign(EVerticalAlignment::VAlign_Bottom)
		.Padding(0.f, 0.f, 250.f, 150.f)
		[
			SAssignNew(VerticalBox, SVerticalBox)
		]
	];

	if (InArgs._bGameSaveExist)
	{
		VerticalBox->AddSlot()
		[
			SNew(SButton)
			.ButtonStyle(&MainMenuStyle.ButtonStyle)
			.TextStyle(&MainMenuStyle.TextStyle)
			.Text(FText::FromString(TEXT("Continue")))
			.OnClicked(this, &SSpaceMainMenuWidget::OnContinueClick)
		];
	}
	VerticalBox->AddSlot()
	[
		SNew(SButton)
		.ButtonStyle(&MainMenuStyle.ButtonStyle)
		.TextStyle(&MainMenuStyle.TextStyle)
		.Text(FText::FromString(TEXT("New Game")))
		.OnClicked(this, &SSpaceMainMenuWidget::OnNewGameClick)
	];
	VerticalBox->AddSlot()
	[
		SNew(SButton)
		.ButtonStyle(&MainMenuStyle.ButtonStyle)
		.TextStyle(&MainMenuStyle.TextStyle)
		.Text(FText::FromString(TEXT("Exit")))
		.OnClicked(this, &SSpaceMainMenuWidget::OnExitClick)
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SSpaceMainMenuWidget::OnContinueClick()
{
	auto GameInstance = static_cast<USpaceGameInstance*>(MainMenuHUD->GetGameInstance());
	GameInstance->LaunchGame(true);

	return FReply::Handled();
}

FReply SSpaceMainMenuWidget::OnNewGameClick()
{
	auto GameInstance = static_cast<USpaceGameInstance*>(MainMenuHUD->GetGameInstance());
	GameInstance->LaunchGame(false);

	return FReply::Handled();
}

FReply SSpaceMainMenuWidget::OnExitClick()
{
	MainMenuHUD->GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
	return FReply::Handled();
}
