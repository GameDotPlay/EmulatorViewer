

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
class UBuildModeUIWidget;

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API AEmulatorViewerHUD : public AHUD
{
	GENERATED_BODY()

public:

	void TogglePause();

	void ShowInteractionModeLabel();

	void HideInteractionModeLabel();

	void ShowBuildModeUI();

	void HideBuildModeUI();

	void SetInteractionModeLabel(FText InteractionModeText);

	UBuildModeUIWidget* GetBuildModeUI() { return this->BuildModeUIWidget; }

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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> BuildModeUIClass;

private:

	UUserWidget* PauseMenu = nullptr;

	UUserWidget* MainMenu = nullptr;

	UPopupContainerWidget* PopupsCanvas = nullptr;

	UInteractionModeLabelWidget* InteractionModeLabelWidget = nullptr;

	UBuildModeUIWidget* BuildModeUIWidget = nullptr;

	void InitializePopupsCanvas();

	void ConfigurePopupCanvasSlot(UCanvasPanelSlot* Slot) const;
};