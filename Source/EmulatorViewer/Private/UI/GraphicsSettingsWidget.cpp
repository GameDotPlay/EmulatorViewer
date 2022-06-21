
#include "UI/GraphicsSettingsWidget.h"
#include "UI/DropDownMenuItemWidget.h"
#include "Components/ComboBoxString.h"
#include "UI/IntegerMenuItemWidget.h"
#include "GameFramework/GameUserSettings.h"

void UGraphicsSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(GEngine))
	{
		this->UserSettings = GEngine->GetGameUserSettings();
	}

	this->InitializeDropDowns();
	this->ResolutionScale->GetTextBox()->OnTextCommitted.AddUniqueDynamic(this, &UGraphicsSettingsWidget::SetResolutionQuality);
	this->ViewDistanceQualityDropDown->GetComboBox()->OnSelectionChanged.AddUniqueDynamic(this, &UGraphicsSettingsWidget::SetViewDistanceQuality);
	this->TextureQualityDropDown->GetComboBox()->OnSelectionChanged.AddUniqueDynamic(this, &UGraphicsSettingsWidget::SetTextureQuality);
	this->ShadowQualityDropDown->GetComboBox()->OnSelectionChanged.AddUniqueDynamic(this, &UGraphicsSettingsWidget::SetShadowQuality);
	this->ShadingQualityDropDown->GetComboBox()->OnSelectionChanged.AddUniqueDynamic(this, &UGraphicsSettingsWidget::SetShadingQuality);
	this->ReflectionQualityDropDown->GetComboBox()->OnSelectionChanged.AddUniqueDynamic(this, &UGraphicsSettingsWidget::SetReflectionQuality);
	this->PostProcessQualityDropDown->GetComboBox()->OnSelectionChanged.AddUniqueDynamic(this, &UGraphicsSettingsWidget::SetPostProcessQuality);
	this->GlobalIlluminationQualityDropDown->GetComboBox()->OnSelectionChanged.AddUniqueDynamic(this, &UGraphicsSettingsWidget::SetGlobalIlluminationQuality);
	this->EffectsQualityDropDown->GetComboBox()->OnSelectionChanged.AddUniqueDynamic(this, &UGraphicsSettingsWidget::SetEffectsQuality);
	this->AntiAliasingQualityDropDown->GetComboBox()->OnSelectionChanged.AddUniqueDynamic(this, &UGraphicsSettingsWidget::SetAntiAliasingQuality);
}

void UGraphicsSettingsWidget::SetResolutionQuality(const FText& Text, ETextCommit::Type CommitMethod)
{
	int32 Value = this->ResolutionScale->GetIntegerValue();

	if (IsValid(this->UserSettings))
	{
		this->UserSettings->SetResolutionScaleValueEx((float)Value);
		this->UserSettings->ApplySettings(false);
		this->UserSettings->SaveSettings();
	}
}

void UGraphicsSettingsWidget::SetViewDistanceQuality(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 Value = this->ViewDistanceQualityDropDown->GetDropDownSelection();

	if (IsValid(this->UserSettings))
	{
		this->UserSettings->SetViewDistanceQuality(Value);
		this->UserSettings->ApplyNonResolutionSettings();
		this->UserSettings->SaveSettings();
	}
}

void UGraphicsSettingsWidget::SetTextureQuality(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 Value = this->TextureQualityDropDown->GetDropDownSelection();

	if (IsValid(this->UserSettings))
	{
		this->UserSettings->SetTextureQuality(Value);
		this->UserSettings->ApplyNonResolutionSettings();
		this->UserSettings->SaveSettings();
	}
}

void UGraphicsSettingsWidget::SetShadowQuality(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 Value = this->ShadowQualityDropDown->GetDropDownSelection();

	if (IsValid(this->UserSettings))
	{
		this->UserSettings->SetShadowQuality(Value);
		this->UserSettings->ApplyNonResolutionSettings();
		this->UserSettings->SaveSettings();
	}
}

void UGraphicsSettingsWidget::SetShadingQuality(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 Value = this->ShadingQualityDropDown->GetDropDownSelection();

	if (IsValid(this->UserSettings))
	{
		this->UserSettings->SetShadingQuality(Value);
		this->UserSettings->ApplyNonResolutionSettings();
		this->UserSettings->SaveSettings();
	}
}

void UGraphicsSettingsWidget::SetReflectionQuality(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 Value = this->ReflectionQualityDropDown->GetDropDownSelection();

	if (IsValid(this->UserSettings))
	{
		this->UserSettings->SetReflectionQuality(Value);
		this->UserSettings->ApplyNonResolutionSettings();
		this->UserSettings->SaveSettings();
	}
}

void UGraphicsSettingsWidget::SetPostProcessQuality(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 Value = this->PostProcessQualityDropDown->GetDropDownSelection();

	if (IsValid(this->UserSettings))
	{
		this->UserSettings->SetPostProcessingQuality(Value);
		this->UserSettings->ApplyNonResolutionSettings();
		this->UserSettings->SaveSettings();
	}
}

void UGraphicsSettingsWidget::SetGlobalIlluminationQuality(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 Value = this->GlobalIlluminationQualityDropDown->GetDropDownSelection();

	if (IsValid(this->UserSettings))
	{
		this->UserSettings->SetGlobalIlluminationQuality(Value);
		this->UserSettings->ApplyNonResolutionSettings();
		this->UserSettings->SaveSettings();
	}
}

void UGraphicsSettingsWidget::SetEffectsQuality(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 Value = this->EffectsQualityDropDown->GetDropDownSelection();

	if (IsValid(this->UserSettings))
	{
		this->UserSettings->SetVisualEffectQuality(Value);
		this->UserSettings->ApplyNonResolutionSettings();
		this->UserSettings->SaveSettings();
	}
}

void UGraphicsSettingsWidget::SetAntiAliasingQuality(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 Value = this->AntiAliasingQualityDropDown->GetDropDownSelection();

	if (IsValid(this->UserSettings))
	{
		this->UserSettings->SetAntiAliasingQuality(Value);
		this->UserSettings->ApplyNonResolutionSettings();
		this->UserSettings->SaveSettings();
	}
}

void UGraphicsSettingsWidget::InitializeDropDowns()
{
	TArray<FString> DefaultOptions = { "Low", "Medium", "High" };

	this->ResolutionScale->SetDescription(FText::FromString(TEXT("Resolution Scale")));
	this->ResolutionScale->SetToolTip(FText::FromString(TEXT("A percent (0-100) that scales the resolution. Lower value gives better performance but at a severe visual quality loss.")));
	if (IsValid(this->UserSettings))
	{
		float CurrentScaleNormalized;
		float CurrentScaleValue;
		float MinScaleValue;
		float MaxScaleValue;
		this->UserSettings->GetResolutionScaleInformationEx(CurrentScaleNormalized, CurrentScaleValue, MinScaleValue, MaxScaleValue);
		this->ResolutionScale->SetValue(FMath::RoundToInt32(CurrentScaleValue));
	}

	this->ViewDistanceQualityDropDown->SetDescription(FText::FromString(TEXT("View Distance Quality")));
	this->ViewDistanceQualityDropDown->SetToolTip(FText::FromString(TEXT("Lower values give shorter view distances. Negligable effect on performance on indoor environments.")));
	this->ViewDistanceQualityDropDown->SetDropDownOptions(DefaultOptions);
	if (IsValid(this->UserSettings))
	{
		this->ViewDistanceQualityDropDown->SetDropDownSelection(this->UserSettings->GetViewDistanceQuality());
	}

	this->TextureQualityDropDown->SetDescription(FText::FromString(TEXT("Texture Quality")));
	this->TextureQualityDropDown->SetToolTip(FText::FromString(TEXT("Lower values give worse texture quality. Small effect on performance.")));
	this->TextureQualityDropDown->SetDropDownOptions(DefaultOptions);
	if (IsValid(this->UserSettings))
	{
		this->TextureQualityDropDown->SetDropDownSelection(this->UserSettings->GetTextureQuality());
	}

	this->ShadowQualityDropDown->SetDescription(FText::FromString(TEXT("Shadow Quality")));
	this->ShadowQualityDropDown->SetToolTip(FText::FromString(TEXT("Lower values give worse shadow quality. Medium effect on performance.")));
	this->ShadowQualityDropDown->SetDropDownOptions(DefaultOptions);
	if (IsValid(this->UserSettings))
	{
		this->ShadowQualityDropDown->SetDropDownSelection(this->UserSettings->GetShadowQuality());
	}

	this->ShadingQualityDropDown->SetDescription(FText::FromString(TEXT("Shading Quality")));
	this->ShadingQualityDropDown->SetToolTip(FText::FromString(TEXT("Lower values give worse shading quality. Small effect on performance.")));
	this->ShadingQualityDropDown->SetDropDownOptions(DefaultOptions);
	if (IsValid(this->UserSettings))
	{
		this->ShadingQualityDropDown->SetDropDownSelection(this->UserSettings->GetShadingQuality());
	}

	this->ReflectionQualityDropDown->SetDescription(FText::FromString(TEXT("Reflection Quality")));
	this->ReflectionQualityDropDown->SetToolTip(FText::FromString(TEXT("Lower values give worse reflection quality. Small effect on performance.")));
	this->ReflectionQualityDropDown->SetDropDownOptions(DefaultOptions);
	if (IsValid(this->UserSettings))
	{
		this->ReflectionQualityDropDown->SetDropDownSelection(this->UserSettings->GetReflectionQuality());
	}

	this->PostProcessQualityDropDown->SetDescription(FText::FromString(TEXT("Post Process Quality")));
	this->PostProcessQualityDropDown->SetToolTip(FText::FromString(TEXT("Lower values give worse post processing quality. Medium effect on performance.")));
	this->PostProcessQualityDropDown->SetDropDownOptions(DefaultOptions);
	if (IsValid(this->UserSettings))
	{
		this->PostProcessQualityDropDown->SetDropDownSelection(this->UserSettings->GetPostProcessingQuality());
	}

	this->GlobalIlluminationQualityDropDown->SetDescription(FText::FromString(TEXT("Global Illumination Quality")));
	this->GlobalIlluminationQualityDropDown->SetToolTip(FText::FromString(TEXT("Lower values give worse lighting quality. Large effect on performance.")));
	this->GlobalIlluminationQualityDropDown->SetDropDownOptions(DefaultOptions);
	if (IsValid(this->UserSettings))
	{
		this->GlobalIlluminationQualityDropDown->SetDropDownSelection(this->UserSettings->GetGlobalIlluminationQuality());
	}

	this->EffectsQualityDropDown->SetDescription(FText::FromString(TEXT("Effects Quality")));
	this->EffectsQualityDropDown->SetToolTip(FText::FromString(TEXT("Lower values give worse effects quality. Small effect on performance.")));
	this->EffectsQualityDropDown->SetDropDownOptions(DefaultOptions);
	if (IsValid(this->UserSettings))
	{
		this->EffectsQualityDropDown->SetDropDownSelection(this->UserSettings->GetVisualEffectQuality());
	}

	this->AntiAliasingQualityDropDown->SetDescription(FText::FromString(TEXT("Antialiasing Quality")));
	this->AntiAliasingQualityDropDown->SetToolTip(FText::FromString(TEXT("Lower values give worse antialiasing quality. Medium effect on performance.")));
	this->AntiAliasingQualityDropDown->SetDropDownOptions(DefaultOptions);
	if (IsValid(this->UserSettings))
	{
		this->AntiAliasingQualityDropDown->SetDropDownSelection(this->UserSettings->GetAntiAliasingQuality());
	}
}