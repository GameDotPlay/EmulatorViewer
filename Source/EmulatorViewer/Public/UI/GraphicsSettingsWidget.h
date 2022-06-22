

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GraphicsSettingsWidget.generated.h"

class UCanvasPanel;
class UBackgroundBlur;
class UVerticalBox;
class UDropDownMenuItemWidget;
class UIntegerMenuItemWidget;

UENUM()
enum class EDropDownValues : int32
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
	UVerticalBox* VerticalBox = nullptr;

	UPROPERTY(meta = (BindWidget))
	UIntegerMenuItemWidget* ResolutionScale = nullptr;

	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* WindowModeDropDown = nullptr;

	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* ViewDistanceQualityDropDown = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* TextureQualityDropDown = nullptr;

	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* ShadowQualityDropDown = nullptr;

	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* ShadingQualityDropDown = nullptr;

	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* ReflectionQualityDropDown = nullptr;

	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* PostProcessQualityDropDown = nullptr;

	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* GlobalIlluminationQualityDropDown = nullptr;

	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* EffectsQualityDropDown = nullptr;

	UPROPERTY(meta = (BindWidget))
	UDropDownMenuItemWidget* AntiAliasingQualityDropDown = nullptr;

	UFUNCTION()
	void SetResolutionQuality(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void SetWindowMode(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void SetViewDistanceQuality(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void SetTextureQuality(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void SetShadowQuality(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void SetShadingQuality(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void SetReflectionQuality(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void SetPostProcessQuality(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void SetGlobalIlluminationQuality(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void SetEffectsQuality(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void SetAntiAliasingQuality(FString SelectedItem, ESelectInfo::Type SelectionType);

	void InitializeDropDowns();

	UGameUserSettings* UserSettings = nullptr;
};