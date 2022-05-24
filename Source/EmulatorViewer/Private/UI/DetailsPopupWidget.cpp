


#include "UI/DetailsPopupWidget.h"
#include "Input/Reply.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"

void UDetailsPopupWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->HeaderWidget->GetButton()->OnClicked.AddUniqueDynamic(this, &UDetailsPopupWidget::ClosePopup);
	this->ParentSlot = Cast<UCanvasPanelSlot>(this->Slot);
}

FReply UDetailsPopupWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	this->bMouseDown = true;

	return FReply::Handled();
}

FReply UDetailsPopupWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	this->bMouseDown = false;

	return FReply::Handled();
}

void UDetailsPopupWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("%d"), this->bMouseDown);

	if (this->bMouseDown)
	{
		/*if (IsValid(this->ParentSlot))
		{
			FVector2D Position = this->ParentSlot->GetPosition();
			UE_LOG(LogTemp, Warning, TEXT("X:%f, Y:%f"), Position.X, Position.Y);
			APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			FVector2D MousePos;
			PC->GetMousePosition(MousePos.X, MousePos.Y);
			this->ParentSlot->SetPosition(MousePos);
		}*/
	}
}
