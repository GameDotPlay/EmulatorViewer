

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FloatInputSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UFloatInputSettingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetToolTip(const FText& InToolTipText);

	float GetFloatValue() const { return this->Value; }

	void SetFloatValue(float InValue);

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* InputTextBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SettingLabel;

protected:

	void NativeConstruct() override;

private:

	float Value = 1.f;

	UFUNCTION()
	void ValidateFloatInput(const FText& Text, ETextCommit::Type CommitMethod);
};