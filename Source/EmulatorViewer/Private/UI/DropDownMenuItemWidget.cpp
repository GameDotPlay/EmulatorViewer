
#include "UI/DropDownMenuItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/ComboBoxKey.h"

void UDropDownMenuItemWidget::SetDescription(FText DescriptionText)
{
	if (!DescriptionText.IsEmptyOrWhitespace())
	{
		this->Description->SetText(DescriptionText);
	}
}

void UDropDownMenuItemWidget::SetToolTip(FText InToolTipText)
{
	if (!InToolTipText.IsEmptyOrWhitespace())
	{
		this->Description->SetToolTipText(InToolTipText);
		this->DropDown->SetToolTipText(InToolTipText);
	}
}