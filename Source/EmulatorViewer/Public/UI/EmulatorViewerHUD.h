

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EmulatorViewerHUD.generated.h"

class UUserWidget;
class UDetailsPopupWidget;
class UCanvasPanel;
class UPopupContainerWidget;

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

	void ShowMainMenu();

	void HideMainMenu();

	void AddDetailsPopup(UDetailsPopupWidget* DetailsPopup);

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PopupsCanvasClass;

private:

	UUserWidget* PauseMenu;

	UUserWidget* MainMenu;

	UPopupContainerWidget* PopupsCanvas;

	void InitializePopupsCanvas();
};