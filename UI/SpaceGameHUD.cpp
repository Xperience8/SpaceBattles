// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpaceGameHUD.h"

#include "../Machines/SpacePlayerSpaceship.h"
#include "../Machines/SpaceSpaceshipMovementComponent.h"
#include "../Machines/SpaceshipParts/SpaceRocketGunComponent.h"

ASpaceGameHUD::ASpaceGameHUD()
{
	ConstructorHelpers::FObjectFinder<UTexture2D> ScopeImage(TEXT("/Game/UI/T_Scope"));
	ConstructorHelpers::FObjectFinder<UTexture2D> RpmMeterImage(TEXT("/Game/UI/T_RpmMeter"));
	ConstructorHelpers::FObjectFinder<UTexture2D> RpmPointerImage(TEXT("/Game/UI/T_RpmPointer"));
	ConstructorHelpers::FObjectFinder<UTexture2D> LifeMeterImage(TEXT("/Game/UI/T_LifeMeter"));
	ConstructorHelpers::FObjectFinder<UTexture2D> RocketImage(TEXT("/Game/UI/T_Rocket"));

	ScopeIcon = UCanvas::MakeIcon(ScopeImage.Object, 0.f, 0.f, 64.f, 64.f);
	RpmMeterIcon = UCanvas::MakeIcon(RpmMeterImage.Object, 0.f, 0.f, 0.f, 0.f);
	RpmPointerIcon = UCanvas::MakeIcon(RpmPointerImage.Object, 0.f, 0.f, 0.f, 0.f);
	LifeMeterIcon = UCanvas::MakeIcon(LifeMeterImage.Object, 0.f, 0.f, 0.f, 0.f);
	RocketIcon = UCanvas::MakeIcon(RocketImage.Object, 0.f, 0.f, 0.f, 0.f);
}

void ASpaceGameHUD::DrawHUD()
{
	Super::DrawHUD();

	auto OwningPawn = static_cast<ASpacePlayerSpaceship*>(GetOwningPawn());
	if (!OwningPawn)
	{
		return;
	}

	// Drawing aiming scope
	float ScaleUI = Canvas->ClipY / 1080.f;

	float ScopeLocationX = (Canvas->ClipX * 0.5f) - (ScopeIcon.UL * 0.5f);
	float ScopeLocationY = (Canvas->ClipY * 0.5f) - (ScopeIcon.VL * 0.5f) + 52.f * ScaleUI;

	Canvas->SetLinearDrawColor(FLinearColor(1.f, 1.f, 1.f, 1.f));
	Canvas->DrawIcon(ScopeIcon, ScopeLocationX, ScopeLocationY, ScaleUI);

	// Drawing rpm meter
	const float RpmLocationX = 100.f * ScaleUI;
	const float RpmLocationY = Canvas->ClipY - (RpmMeterIcon.VL * ScaleUI);
	
	Canvas->DrawIcon(RpmMeterIcon, RpmLocationX, RpmLocationY, ScaleUI);
	
	static const float MinRpmToRotation = 62.5f;
	static const float MaxRpmToRotation = 337.f;

	float EngineRpm = static_cast<USpaceSpaceshipMovementComponent*>(OwningPawn->GetMovementComponent())->GetEngineRpmFactor();
	float CurrentEngineRpmRotation = FMath::Lerp(MinRpmToRotation, MaxRpmToRotation, EngineRpm);

	FCanvasTileItem RpmPointerItem(FVector2D(RpmLocationX, RpmLocationY), RpmPointerIcon.Texture->Resource, FLinearColor(1.f, 1.f, 1.f, 1.f));
	RpmPointerItem.BlendMode = ESimpleElementBlendMode::SE_BLEND_Translucent;
	RpmPointerItem.Size = FVector2D(RpmPointerIcon.UL * ScaleUI, RpmPointerIcon.VL * ScaleUI);
	RpmPointerItem.Rotation = FRotator(0, CurrentEngineRpmRotation, 0);
	RpmPointerItem.PivotPoint = FVector2D(0.5f, 0.5f);
	
	Canvas->DrawItem(RpmPointerItem);

	// Drawing life meter
	float LifeMeterLocationX = Canvas->ClipX - 500.f * ScaleUI;
	float LifeMeterLocationY = Canvas->ClipY - 200.f * ScaleUI;
	
	float LifeFactor = OwningPawn->GetLifeFactor();

	FCanvasTileItem CurrentLifeMeter(FVector2D(LifeMeterLocationX + 40.f * ScaleUI, LifeMeterLocationY), FVector2D(400.f * ScaleUI, 100.f * ScaleUI),  LifeFactor > 0.25f ? FLinearColor::Green : FLinearColor::Red);
	CurrentLifeMeter.Size.X *= LifeFactor;
	Canvas->DrawItem(CurrentLifeMeter);

	FCanvasTileItem LifeMeter(FVector2D(LifeMeterLocationX, LifeMeterLocationY), LifeMeterIcon.Texture->Resource, FVector2D(440.f * ScaleUI, 100.f * ScaleUI), FLinearColor::White);
	LifeMeter.BlendMode = ESimpleElementBlendMode::SE_BLEND_Translucent;
	Canvas->DrawItem(LifeMeter);

	// Drawing rocket meter
	float RocketMeterLocationX = LifeMeterLocationX + 10.f * ScaleUI;
	float RocketMeterLocationY = LifeMeterLocationY - 50.f * ScaleUI;

	int32 NumRockets = OwningPawn->GetRocketGunComponent()->GetNumRockets();

	FCanvasTileItem RocketMeter(FVector2D(RocketMeterLocationX, RocketMeterLocationY), RocketIcon.Texture->Resource, FVector2D(50.f * ScaleUI, 50.f * ScaleUI), FLinearColor::White);
	RocketMeter.BlendMode = ESimpleElementBlendMode::SE_BLEND_Translucent;
	RocketMeter.Size.X *= NumRockets;
	RocketMeter.UV1.X *= NumRockets;
	Canvas->DrawItem(RocketMeter);
}
