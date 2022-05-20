

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

protected:

	virtual void NativeConstruct() override;

private:

	class USizeBox* Parent;

	class UBorder* HeaderBorder;

	class UHorizontalBox* HorizontalBox;

	class UTextBlock* HeaderText;

	class USizeBox* ButtonSizer;

	class UButton* CloseButton;

	class UTextBlock* CloseButtonText;

	void InitializeSettings();
};
