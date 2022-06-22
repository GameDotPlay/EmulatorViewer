#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
#include "DropDownMenuItemWidget.generated.h"

class UTextBlock;
class UHorizontalBox;

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UDropDownMenuItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UComboBoxString* GetComboBox() const { return this->DropDown; }

	UHorizontalBox* GetHorizontalBox() const { return this->HorizontalBox; }

	void SetDropDownSelection(int32 Value, const FString& OptionText);

	int32 GetDropDownSelection() const { return this->DropDown->GetSelectedIndex(); }

	void SetDescription(const FText& DescriptionText);

	void SetToolTip(const FText& InToolTipText);

	void SetDropDownOptions(const TArray<FString>& Options);

protected:

private:

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Description = nullptr;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* DropDown = nullptr;
};