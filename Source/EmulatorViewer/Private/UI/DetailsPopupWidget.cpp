


#include "UI/DetailsPopupWidget.h"
#include "Input/Reply.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"

void UDetailsPopupWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->HeaderWidget->GetButton()->OnClicked.AddUniqueDynamic(this, &UDetailsPopupWidget::ClosePopup);
	this->ParentSlot = Cast<UCanvasPanelSlot>(this->Slot);

	this->PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

FReply UDetailsPopupWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	/*const TShared
	FReply Reply = FReply::DetectDrag()*/


	return FReply::Handled();
}

FReply UDetailsPopupWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	
	return FReply::Handled();
}

void UDetailsPopupWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	this->bMouseDown = true;
}

void UDetailsPopupWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	this->bMouseDown = false;
}

void UDetailsPopupWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (this->bMouseDown)
	{
		if (IsValid(this->ParentSlot))
		{
			FVector2D MousePos;
			this->PlayerController->GetMousePosition(MousePos.X, MousePos.Y);
			this->ParentSlot->SetPosition(MousePos);
		}
	}
}
