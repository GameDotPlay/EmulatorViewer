

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "DetailsPopupHeaderWidget.generated.h"

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UDetailsPopupHeaderWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetHeaderText(const FText& InHeaderText) { this->HeaderText->SetText(InHeaderText); }

	UButton* GetButton() const { return this->CloseButton; }

protected:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HeaderText = nullptr;

	UPROPERTY(meta=(BindWidget))
	UButton* CloseButton = nullptr;
};
