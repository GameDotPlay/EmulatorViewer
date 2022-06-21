
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "IntegerMenuItemWidget.generated.h"

class UTextBlock;
class UHorizontalBox;

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UIntegerMenuItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UEditableTextBox* GetTextBox() const { return this->IntegerInput; }

	UHorizontalBox* GetHorizontalBox() const { return this->HorizontalBox; }

	FText GetTextValue() const { return this->IntegerInput->GetText(); }

	int32 GetIntegerValue() const { return this->Value; }

	void SetValue(const FText& InText);

	void SetValue(const int32 InValue);

	void SetDescription(const FText& DescriptionText);

	void SetToolTip(const FText& InToolTipText);

protected:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Description = nullptr;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* IntegerInput = nullptr;

	int32 Value;

	UFUNCTION()
	void ValidateIntegerInput(const FText& Text, ETextCommit::Type CommitMethod);
};