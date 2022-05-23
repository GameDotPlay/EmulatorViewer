


#include "UI/EmulatorViewerHUD.h"
#include "UI/DetailsPopupWidget.h"
#include "UI/PopupContainerWidget.h"
#include "Components/CanvasPanel.h"

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
	}
}

void AEmulatorViewerHUD::InitializePopupsCanvas()
{
	//this->PopupsCanvas = Cast<UPopupContainerWidget>(CreateWidget(this, this->PopupsCanvasClass));
	//this->PopupsCanvas->AddToViewport();
}