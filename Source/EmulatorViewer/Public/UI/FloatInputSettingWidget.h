

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "FloatInputSettingWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTextInputValidated, float, Value);

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UFloatInputSettingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	FOnTextInputValidated OnTextInputValidatedDelegate;

	float GetValue() const { return this->Value; }

	FText GetValueText() const { return this->InputTextBox->Text; }

	UEditableTextBox* GetEditableTextBoxWidget() const { return this->InputTextBox; }

	void SetValue(float InValue);

	void SetEnabledState(bool bEnabled) { this->InputTextBox->SetIsEnabled(bEnabled); }

	void SetToolTip(const FText& InToolTipText = FText::GetEmpty());

	void SetLabel(const FText& InLabelText);

protected:

	void NativeConstruct() override;

private:

	float Value = 1.f;

	UFUNCTION()
	void ValidateFloatInput(const FText& Text, ETextCommit::Type CommitMethod);

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* InputTextBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SettingLabel;
};