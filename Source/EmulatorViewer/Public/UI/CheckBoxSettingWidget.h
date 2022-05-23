#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CheckBoxSettingWidget.generated.h"

class UCheckBox;
class UTextBlock;

UCLASS()
class EMULATORVIEWER_API UCheckBoxSettingWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetToolTip(const FText& InToolTipText = FText::GetEmpty());

	void SetLabel(const FText& InLabelText);

	void SetCheckedState(ECheckBoxState InitialState);

	void SetEnabledState(bool bEnabled);

	UCheckBox* GetCheckBoxWidget() const { return this->CheckBox; }

protected:

	void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	UCheckBox* CheckBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Label;
};