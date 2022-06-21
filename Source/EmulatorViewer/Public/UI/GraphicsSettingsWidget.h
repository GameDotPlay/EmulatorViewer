

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GraphicsSettingsWidget.generated.h"

class UCanvasPanel;
class UBackgroundBlur;
class UVerticalBox;
class UDropDownMenuItemWidget;

UENUM()
enum class FDropDownValues
{
	Low = 0,
	Medium = 1,
	High = 2
};

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UGraphicsSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

protected:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* BaseCanvas;

	UPROPERTY(meta = (BindWidget))
	UBackgroundBlur* BackgroundBlur;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox;

	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* ViewDistanceQualityDropDown;
	
	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* TextureQualityDropDown;

	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* ShadowQualityDropDown;

	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* ShadingQualityDropDown;

	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* ReflectionQualityDropDown;

	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* PostProcessQualityDropDown;

	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* GlobalIlluminationQualityDropDown;

	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* EffectsQualityDropDown;

	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* AntiAliasingQualityDropDown;

	void SetViewDistanceQuality(FName SelectedItem, ESelectInfo::Type SelectionType);

	void InitializeDropDowns();
};