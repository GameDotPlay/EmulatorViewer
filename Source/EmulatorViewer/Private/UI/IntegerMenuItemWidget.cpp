
#include "UI/IntegerMenuItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"

void UIntegerMenuItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->IntegerInput->OnTextCommitted.AddUniqueDynamic(this, &UIntegerMenuItemWidget::ValidateIntegerInput);
}

void UIntegerMenuItemWidget::ValidateIntegerInput(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (Text.IsEmptyOrWhitespace() || !Text.IsNumeric())
	{
		this->SetValue(this->Value);
		return;
	}

	this->Value = FCString::Atoi(*Text.ToString());
	this->SetValue(this->Value);
}

void UIntegerMenuItemWidget::SetValue(const FText& InText)
{
	this->ValidateIntegerInput(InText, ETextCommit::Default);
}

void UIntegerMenuItemWidget::SetValue(const int32 InValue)
{
	this->Value = InValue;
	this->IntegerInput->SetText(FText::AsNumber(InValue));
}

void UIntegerMenuItemWidget::SetDescription(const FText& DescriptionText)
{
	if (!DescriptionText.IsEmptyOrWhitespace() && !DescriptionText.IsNumeric())
	{
		this->Description->SetText(DescriptionText);
	}
}

void UIntegerMenuItemWidget::SetToolTip(const FText& InToolTipText)
{
	if (!InToolTipText.IsEmptyOrWhitespace() && !InToolTipText.IsNumeric())
	{
		this->Description->SetToolTipText(InToolTipText);
		this->IntegerInput->SetToolTipText(InToolTipText);
	}
}