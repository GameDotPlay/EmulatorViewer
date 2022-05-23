

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DetailsPopupHeaderWidget.generated.h"

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UDetailsPopupHeaderWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetHeaderText(const FText& InHeaderText);

protected:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HeaderText = nullptr;

	UPROPERTY(meta=(BindWidget))
	class UButton* CloseButton = nullptr;
};
