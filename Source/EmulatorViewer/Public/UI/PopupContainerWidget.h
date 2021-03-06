

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PopupContainerWidget.generated.h"

class UCanvasPanel;
class UCanvasPanelSlot;

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UPopupContainerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UCanvasPanelSlot* AddPopup(UUserWidget* Popup) const;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

protected:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* PopupsCanvas;
};
