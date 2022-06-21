
#include "UI/GraphicsSettingsWidget.h"
#include "UI/DropDownMenuItemWidget.h"
#include "Components/ComboBoxKey.h"

void UGraphicsSettingsWidget::NativeConstruct()
{
	this->ViewDistanceQualityDropDown->GetComboBox()->OnSelectionChanged.AddUniqueDynamic(this, &UGraphicsSettingsWidget::SetViewDistanceQuality);
}

void UGraphicsSettingsWidget::SetViewDistanceQuality(FName SelectedItem, ESelectInfo::Type SelectionType)
{

}

void UGraphicsSettingsWidget::InitializeDropDowns()
{
	this->ViewDistanceQualityDropDown->SetDescription(FText::FromString(TEXT("View Distance Quality")));
	this->ViewDistanceQualityDropDown->SetToolTip(FText::FromString(TEXT("Lower values give lower view distances. Small effect on performance.")));
	this->ViewDistanceQualityDropDown->GetComboBox()->AddOption(FName(TEXT("Low")));
	this->ViewDistanceQualityDropDown->GetComboBox()->AddOption(FName(TEXT("Medium")));
	this->ViewDistanceQualityDropDown->GetComboBox()->AddOption(FName(TEXT("High")));
}