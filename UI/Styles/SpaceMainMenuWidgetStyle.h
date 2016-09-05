// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once


#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"

#include "SpaceMainMenuWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct SPACEBATTLES_API FSpaceMainMenuStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FSpaceMainMenuStyle();
	virtual ~FSpaceMainMenuStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FSpaceMainMenuStyle& GetDefault();

	UPROPERTY(EditAnywhere)
	FSlateBrush BackgroundImage;

	UPROPERTY(EditAnywhere)	
	FButtonStyle ButtonStyle;

	UPROPERTY(EditAnywhere)
	FTextBlockStyle TextStyle;
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class USpaceMainMenuWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FSpaceMainMenuStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
