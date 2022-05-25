


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
		this->SetValue(this->Value);
		this->OnTextInputValidatedDelegate.Broadcast(this->Value);
		return;
	}

	this->Value = FCString::Atof(*Text.ToString());
	this->SetValue(this->Value);

	this->OnTextInputValidatedDelegate.Broadcast(this->Value);
}

void UFloatInputSettingWidget::SetToolTip(const FText& InToolTipText)
{
	this->InputTextBox->SetToolTipText(InToolTipText);
	this->SettingLabel->SetToolTipText(InToolTipText);
}

void UFloatInputSettingWidget::SetLabel(const FText& InLabelText)
{
	this->SettingLabel->SetText(InLabelText);
}

void UFloatInputSettingWidget::SetValue(float InValue)
{
	this->Value = InValue;
	this->InputTextBox->SetText(FText::AsNumber(InValue));
}