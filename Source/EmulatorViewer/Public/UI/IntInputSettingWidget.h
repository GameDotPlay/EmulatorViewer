

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IntInputSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UIntInputSettingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetToolTip(const FText& InToolTipText);

	int32 GetIntValue() const { return this->Value; }

	void SetIntValue(int32 InValue);

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* InputTextBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SettingLabel;

protected:

	void NativeConstruct() override;

private:

	int32 Value = 0;

	void ValidateIntInput(const FText& Text, ETextCommit::Type CommitMethod);

};
