
#include "UI/CheckBoxSettingWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void UCheckBoxSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCheckBoxSettingWidget::SetToolTip(const FText& InToolTipText)
{
	this->CheckBox->SetToolTipText(InToolTipText);
	this->Label->SetToolTipText(InToolTipText);
}

void UCheckBoxSettingWidget::SetLabel(const FText& InLabelText)
{
	if (!InLabelText.IsEmptyOrWhitespace())
	{
		this->Label->SetText(InLabelText);
	}
	else
	{
		this->Label->SetText(FText::FromString(TEXT("InLabelText not valid.")));
	}
}

void UCheckBoxSettingWidget::SetCheckedState(ECheckBoxState NewState)
{
	this->CheckBox->SetCheckedState(NewState);
}

void UCheckBoxSettingWidget::SetEnabledState(bool bEnabled)
{
	this->CheckBox->SetIsEnabled(bIsEnabled);
}