


#include "UI/DetailsPopupContentWidget.h"
#include "UI/CheckBoxSettingWidget.h"
#include "Components/VerticalBox.h"
#include "Components/CheckBox.h"
#include "UI/FloatInputSettingWidget.h"

void UDetailsPopupContentWidget::NativeConstruct()
{

}

UCheckBox* UDetailsPopupContentWidget::AddCheckBoxRow(bool bInitialCheckedState, bool bEnabled, const FText& InDescription, const FText& InToolTipText /*= FText::GetEmpty()*/)
{
	UCheckBoxSettingWidget* CheckBoxSetting = Cast<UCheckBoxSettingWidget>(CreateWidget(this, this->CheckBoxSettingClass));
	if (!IsValid(CheckBoxSetting))
	{
		return nullptr;
	}

	CheckBoxSetting->SetLabel(InDescription);
	CheckBoxSetting->SetToolTip(InToolTipText);
	CheckBoxSetting->SetCheckedState(bInitialCheckedState ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	CheckBoxSetting->SetEnabledState(bEnabled);

	this->BaseVerticalBox->AddChild(CheckBoxSetting);
	this->Rows.Emplace(CheckBoxSetting);

	return CheckBoxSetting->GetCheckBoxWidget();
}

UFloatInputSettingWidget* UDetailsPopupContentWidget::AddFloatInputRow(const float InitialValue, bool bEnabled, const FText& InDescription, const FText& InToolTipText /*= FText::GetEmpty()*/)
{
	UFloatInputSettingWidget* FloatInputSetting = Cast<UFloatInputSettingWidget>(CreateWidget(this, this->FloatInputSettingClass));
	if (!IsValid(FloatInputSetting))
	{
		return nullptr;
	}

	FloatInputSetting->SetValue(InitialValue);
	FloatInputSetting->SetLabel(InDescription);
	FloatInputSetting->SetToolTip(InToolTipText);
	FloatInputSetting->SetEnabledState(bEnabled);

	this->BaseVerticalBox->AddChild(FloatInputSetting);
	this->Rows.Emplace(FloatInputSetting);

	return FloatInputSetting;
}