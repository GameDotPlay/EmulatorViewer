


#include "UI/PopupContainerWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Widget.h"

UCanvasPanelSlot* UPopupContainerWidget::AddPopup(UUserWidget* Popup) const
{
	if (IsValid(Popup))
	{
		return this->PopupsCanvas->AddChildToCanvas(Popup);
	}

	return nullptr;
}

void UPopupContainerWidget::NativeConstruct()
{

}