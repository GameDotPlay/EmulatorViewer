
#include "UI/CheckBoxSettingWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void UCheckBoxSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCheckBoxSettingWidget::SetToolTip(FText InToolTipText)
{
	this->CheckBox->SetToolTipText(InToolTipText);
	this->SettingLabel->SetToolTipText(InToolTipText);
}