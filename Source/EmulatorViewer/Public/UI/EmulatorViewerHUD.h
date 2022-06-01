

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EmulatorViewerHUD.generated.h"

class UUserWidget;
class UDetailsPopupWidget;
class UCanvasPanel;
class UPopupContainerWidget;
class UCanvasPanelSlot;
class UInteractionModeLabelWidget;

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API AEmulatorViewerHUD : public AHUD
{
	GENERATED_BODY()

public:

	void ShowPauseMenu();

	void HidePauseMenu();

	void ShowInteractionModeLabel();

	void HideInteractionModeLabel();

	void AddDetailsPopup(UDetailsPopupWidget* DetailsPopup);

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PopupsCanvasClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> InteractionModeLabelClass;

private:

	UUserWidget* PauseMenu = nullptr;

	UUserWidget* MainMenu = nullptr;

	UPopupContainerWidget* PopupsCanvas = nullptr;

	UInteractionModeLabelWidget* InteractionModeLabelWidget = nullptr;

	void InitializePopupsCanvas();

	void ConfigurePopupCanvasSlot(UCanvasPanelSlot* Slot) const;
};