#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropDownMenuItemWidget.generated.h"

class UTextBlock;
class UComboBoxKey;
class UHorizontalBox;
class UComboBox;

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UDropDownMenuItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UComboBoxKey* GetComboBox() { return this->DropDown; }

	UHorizontalBox* GetHorizontalBox() { return this->HorizontalBox; }

	void SetDescription(FText DescriptionText);

	void SetToolTip(FText InToolTipText);

protected:

private:

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Description;

	UPROPERTY(meta = (BindWidget))
	UComboBoxKey* DropDown;
};
