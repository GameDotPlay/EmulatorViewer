


#include "UI/EmulatorViewerHUD.h"
#include "UI/DetailsPopupWidget.h"
#include "UI/PopupContainerWidget.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanelSlot.h"

void AEmulatorViewerHUD::ShowPauseMenu()
{

}

void AEmulatorViewerHUD::HidePauseMenu()
{

}

void AEmulatorViewerHUD::ShowMainMenu()
{

}

void AEmulatorViewerHUD::HideMainMenu()
{

}

void AEmulatorViewerHUD::AddDetailsPopup(UDetailsPopupWidget* DetailsPopup)
{
	if (DetailsPopup)
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
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		FVector2D MousePos;
		PC->GetMousePosition(MousePos.X, MousePos.Y);
		Slot->SetPosition(MousePos);
	}
}