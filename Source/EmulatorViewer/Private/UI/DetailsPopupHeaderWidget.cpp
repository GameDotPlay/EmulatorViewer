
#include "UI/DetailsPopupHeaderWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UDetailsPopupHeaderWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDetailsPopupHeaderWidget::SetHeaderText(const FText& InHeaderText)
{
	this->HeaderText->SetText(InHeaderText);
}