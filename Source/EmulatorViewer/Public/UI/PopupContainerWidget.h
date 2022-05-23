

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PopupContainerWidget.generated.h"

class UCanvasPanel;

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UPopupContainerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void AddPopup(UUserWidget* Popup) const;

protected:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* PopupsCanvas;
};
