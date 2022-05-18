


#include "UI/FloatInputSettingWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

void UFloatInputSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->InputTextBox->OnTextCommitted.AddUniqueDynamic(this, &UFloatInputSettingWidget::ValidateFloatInput);
}

void UFloatInputSettingWidget::ValidateFloatInput(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (Text.IsEmptyOrWhitespace() || !Text.IsNumeric())
	{
		this->SetFloatValue(this->Value);
	}

	this->Value = FCString::Atof(*Text.ToString());
}

void UFloatInputSettingWidget::SetToolTip(const FText& InToolTipText)
{
	this->InputTextBox->SetToolTipText(InToolTipText);
	this->SettingLabel->SetToolTipText(InToolTipText);
}

void UFloatInputSettingWidget::SetFloatValue(float InValue)
{
	FText TextValue = FText::AsNumber(InValue);
	this->InputTextBox->SetText(TextValue);
	this->Value = InValue;
}