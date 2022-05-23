


#include "UI/DetailsPopupContentWidget.h"
#include "UI/CheckBoxSettingWidget.h"
#include "Components/VerticalBox.h"
#include "Components/CheckBox.h"

void UDetailsPopupContentWidget::NativeConstruct()
{

}

void UDetailsPopupContentWidget::AddRow(TSubclassOf<UUserWidget> UserWidget)
{

}

UCheckBox* UDetailsPopupContentWidget::AddCheckBoxRow(ECheckBoxState InitialCheckedState, bool bEnabled, const FText& InDescription, const FText& InToolTipText /*= FText::GetEmpty()*/)
{
	UCheckBoxSettingWidget* CheckBoxSetting = Cast<UCheckBoxSettingWidget>(CreateWidget(this, this->CheckBoxSettingClass));
	if (!IsValid(CheckBoxSetting))
	{
		return nullptr;
	}

	CheckBoxSetting->SetLabel(InDescription);
	CheckBoxSetting->SetToolTip(InToolTipText);
	CheckBoxSetting->SetCheckedState(InitialCheckedState);
	CheckBoxSetting->SetEnabledState(bEnabled);

	this->BaseVerticalBox->AddChild(CheckBoxSetting);
	this->Rows.Emplace(CheckBoxSetting);

	return CheckBoxSetting->GetCheckBoxWidget();
}