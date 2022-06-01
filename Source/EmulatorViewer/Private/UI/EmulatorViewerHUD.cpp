


#include "UI/EmulatorViewerHUD.h"
#include "UI/DetailsPopupWidget.h"
#include "UI/PopupContainerWidget.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanelSlot.h"
#include "UI/InteractionModeLabelWidget.h"

void AEmulatorViewerHUD::ShowPauseMenu()
{

}

void AEmulatorViewerHUD::HidePauseMenu()
{

}

void AEmulatorViewerHUD::ShowInteractionModeLabel()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	this->InteractionModeLabelWidget = Cast<UInteractionModeLabelWidget>(CreateWidget(PC, this->InteractionModeLabelClass, FName(TEXT("InteractionModeLabelWidget"))));
	if (IsValid(this->InteractionModeLabelWidget))
	{
		this->InteractionModeLabelWidget->AddToViewport();
	}
}

void AEmulatorViewerHUD::HideInteractionModeLabel()
{
	if (IsValid(this->InteractionModeLabelWidget))
	{
		this->InteractionModeLabelWidget->RemoveFromParent();
	}
}

void AEmulatorViewerHUD::AddDetailsPopup(UDetailsPopupWidget* DetailsPopup)
{
	if (IsValid(DetailsPopup))
	{
		if (this->PopupsCanvas == nullptr || !this->PopupsCanvas->IsInViewport())
		{
			this->InitializePopupsCanvas();
		}

		UCanvasPanelSlot* Slot = this->PopupsCanvas->AddPopup(DetailsPopup);
		this->ConfigurePopupCanvasSlot(Slot);
	}
}

void AEmulatorViewerHUD::InitializePopupsCanvas()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	this->PopupsCanvas = Cast<UPopupContainerWidget>(CreateWidget(PC, this->PopupsCanvasClass));
	this->PopupsCanvas->AddToViewport();
}

void AEmulatorViewerHUD::ConfigurePopupCanvasSlot(UCanvasPanelSlot* Slot) const
{
	if (IsValid(Slot))
	{
		Slot->SetAutoSize(true);
		FAnchors Anchors = FAnchors(0, 0, 0, 0);
		Slot->SetAnchors(Anchors);
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		FVector2D MousePos;
		PC->GetMousePosition(MousePos.X, MousePos.Y);
		Slot->SetPosition(MousePos);
	}
}