


#include "UI/CheckBoxSettingWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void UCheckBoxSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->HorizontalContainer->AddChild(this->CheckBox);
	this->HorizontalContainer->AddChild(this->SettingLabel);
}

ECheckBoxState UCheckBoxSettingWidget::GetCheckBoxValue()
{
	return this->CheckBox->GetCheckedState();
}

void UCheckBoxSettingWidget::SetLabelText(FText LabelText)
{
	this->SettingLabel->SetText(LabelText);
}

void UCheckBoxSettingWidget::SetSettingToolTip(FText InToolTipText)
{
	this->CheckBox->SetToolTipText(InToolTipText);
	this->SettingLabel->SetToolTipText(InToolTipText);
}