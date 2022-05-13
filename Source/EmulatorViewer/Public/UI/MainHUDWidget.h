

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class EMULATORVIEWER_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* InteractionModeLabel;

	void SetInteractionModeText(FText InteractionModeText);

protected:

	virtual void NativeConstruct() override;

private:


};