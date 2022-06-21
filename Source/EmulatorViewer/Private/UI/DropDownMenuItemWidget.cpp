
#include "UI/DropDownMenuItemWidget.h"
#include "Components/TextBlock.h"

void UDropDownMenuItemWidget::SetDescription(const FText& DescriptionText)
{
	if (!DescriptionText.IsEmptyOrWhitespace() && !DescriptionText.IsNumeric())
	{
		this->Description->SetText(DescriptionText);
	}
}

void UDropDownMenuItemWidget::SetToolTip(const FText& InToolTipText)
{
	if (!InToolTipText.IsEmptyOrWhitespace() && !InToolTipText.IsNumeric())
	{
		this->Description->SetToolTipText(InToolTipText);
		this->DropDown->SetToolTipText(InToolTipText);
	}
}

void UDropDownMenuItemWidget::SetDropDownOptions(const TArray<FString>& Options)
{
	if (Options.Num() > 0)
	{
		for (int32 i = 0; i < Options.Num(); i++)
		{
			this->DropDown->AddOption(Options[i]);
		}
	}
}