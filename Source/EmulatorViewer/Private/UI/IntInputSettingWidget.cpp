


#include "UI/IntInputSettingWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

void UIntInputSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->InputTextBox->OnTextCommitted.AddUniqueDynamic(this, &UIntInputSettingWidget::ValidateIntInput);
}

void UIntInputSettingWidget::ValidateIntInput(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (Text.IsEmptyOrWhitespace() || !Text.IsNumeric())
	{
		this->SetIntValue(this->Value);
	}

	this->Value = FCString::Atoi(*Text.ToString());
}

void UIntInputSettingWidget::SetToolTip(const FText& InToolTipText)
{
	this->InputTextBox->SetToolTipText(InToolTipText);
	this->SettingLabel->SetToolTipText(InToolTipText);
}

void UIntInputSettingWidget::SetIntValue(int32 InValue)
{
	FText TextValue = FText::AsNumber(InValue);
	this->InputTextBox->SetText(TextValue);
	this->Value = InValue;
}