


#include "UI/DetailsPopupWidget.h"

void UDetailsPopupWidget::NativeConstruct()
{
	this->HeaderWidget->GetButton()->OnClicked.AddUniqueDynamic(this, &UDetailsPopupWidget::ClosePopup);
}