

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DetailsPopupContentWidget.h"
#include "DetailsPopupHeaderWidget.h"
#include "Input/Reply.h"
#include "DetailsPopupWidget.generated.h"

class UCanvasPanelSlot;

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UDetailsPopupWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UDetailsPopupContentWidget* GetContentWidget() { return this->ContentWidget; }

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetHeaderText(const FText& HeaderText) { this->HeaderWidget->SetHeaderText(HeaderText); }

	UFUNCTION()
	void ClosePopup() { this->RemoveFromParent(); }

protected:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta=(BindWidget))
	UDetailsPopupHeaderWidget* HeaderWidget;

	UPROPERTY(meta = (BindWidget))
	UDetailsPopupContentWidget* ContentWidget;

	bool bMouseDown = false;

	UCanvasPanelSlot* ParentSlot = nullptr;

	APlayerController* PlayerController = nullptr;
};
