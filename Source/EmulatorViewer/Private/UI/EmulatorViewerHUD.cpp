


#include "UI/EmulatorViewerHUD.h"
#include "UI/DetailsPopupWidget.h"
#include "UI/PopupContainerWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "UI/InteractionModeLabelWidget.h"
#include "UI/BuildModeUIWidget.h"

void AEmulatorViewerHUD::TogglePause()
{

}

void AEmulatorViewerHUD::ShowInteractionModeLabel()
{
	this->InteractionModeLabelWidget = Cast<UInteractionModeLabelWidget>(CreateWidget(this->PlayerOwner->GetClass(), this->InteractionModeLabelClass, FName(TEXT("InteractionModeLabelWidget"))));
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

void AEmulatorViewerHUD::ShowBuildModeUI()
{
	this->BuildModeUIWidget = Cast<UBuildModeUIWidget>(CreateWidget(this->PlayerOwner->GetClass(), this->BuildModeUIClass, FName(TEXT("BuildModeUI"))));
	if (IsValid(this->BuildModeUIWidget))
	{
		this->BuildModeUIWidget->AddToViewport();
	}
}

void AEmulatorViewerHUD::HideBuildModeUI()
{
	if (IsValid(this->BuildModeUIWidget))
	{
		this->BuildModeUIWidget->RemoveFromParent();
	}
}

void AEmulatorViewerHUD::SetInteractionModeLabel(FText InteractionModeText)
{
	if (IsValid(this->InteractionModeLabelWidget) && !InteractionModeText.IsEmptyOrWhitespace())
	{
		this->InteractionModeLabelWidget->SetInteractionModeText(InteractionModeText);
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
	this->PopupsCanvas = Cast<UPopupContainerWidget>(CreateWidget(this->PlayerOwner->GetClass(), this->PopupsCanvasClass));
	this->PopupsCanvas->AddToViewport();
}

void AEmulatorViewerHUD::ConfigurePopupCanvasSlot(UCanvasPanelSlot* Slot) const
{
	if (IsValid(Slot))
	{
		Slot->SetAutoSize(true);
		FAnchors Anchors = FAnchors(0, 0, 0, 0);
		Slot->SetAnchors(Anchors);
		FVector2D MousePos;
		this->PlayerOwner->GetMousePosition(MousePos.X, MousePos.Y);
		Slot->SetPosition(MousePos);
	}
}