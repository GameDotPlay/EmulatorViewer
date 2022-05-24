


#include "UI/EmulatorViewerHUD.h"
#include "UI/DetailsPopupWidget.h"
#include "UI/PopupContainerWidget.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"

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
		if (!this->PopupsCanvas->IsInViewport())
		{
			this->InitializePopupsCanvas();
		}

		DetailsPopup->AddToViewport();
	}
}

void AEmulatorViewerHUD::InitializePopupsCanvas()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	this->PopupsCanvas = Cast<UPopupContainerWidget>(CreateWidget(PC, this->PopupsCanvasClass));
	this->PopupsCanvas->AddToViewport();
}