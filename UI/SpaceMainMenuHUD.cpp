// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceMainMenuHUD.h"

#include "Widgets/SSpaceMainMenuWidget.h"

#include "../SpaceGameInstance.h"

void ASpaceMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	auto GameInstance = static_cast<USpaceGameInstance*>(GetGameInstance());
	
	SAssignNew(MainMenuWidget, SSpaceMainMenuWidget).HUD(this).bGameSaveExist(GameInstance->DoesGameSaveExist());
	GEngine->GameViewport->AddViewportWidgetContent(MainMenuWidget.ToSharedRef());

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewport(true);
	InputMode.SetWidgetToFocus(MainMenuWidget);
	GetOwningPlayerController()->SetInputMode(InputMode);
	GetOwningPlayerController()->bShowMouseCursor = true;
}

void ASpaceMainMenuHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GEngine->GameViewport->RemoveViewportWidgetContent(MainMenuWidget.ToSharedRef());
	
	FInputModeGameOnly InputMode;
	GetOwningPlayerController()->SetInputMode(InputMode);
	GetOwningPlayerController()->bShowMouseCursor = false;
}
