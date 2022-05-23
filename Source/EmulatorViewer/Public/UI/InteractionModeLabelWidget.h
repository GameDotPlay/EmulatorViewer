

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionModeLabelWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class EMULATORVIEWER_API UInteractionModeLabelWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* InteractionModeLabel;

	void SetInteractionModeText(FText InteractionModeText);

protected:

	virtual void NativeConstruct() override;

private:
};