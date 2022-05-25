


#include "UI/PopupContainerWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Widget.h"
#include "UI/DragWidget.h"

void UPopupContainerWidget::NativeConstruct()
{

}

UCanvasPanelSlot* UPopupContainerWidget::AddPopup(UUserWidget* Popup) const
{
	if (IsValid(Popup))
	{
		return this->PopupsCanvas->AddChildToCanvas(Popup);
	}

	return nullptr;
}

bool UPopupContainerWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UDragWidget* DragWidgetResult = Cast<UDragWidget>(InOperation);

	if (!IsValid(DragWidgetResult))
	{
		UE_LOG(LogTemp, Warning, TEXT("DragDrop cast failed."));
		return false;
	}

	const FVector2D DragWindowOffset = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	const FVector2D DragWindowOffsetResult = DragWindowOffset - DragWidgetResult->DragOffset;

	DragWidgetResult->WidgetReference->AddToViewport();
	DragWidgetResult->WidgetReference->SetVisibility(ESlateVisibility::Visible);
	DragWidgetResult->WidgetReference->SetPositionInViewport(DragWindowOffsetResult, false);

	return true;
}