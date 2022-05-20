
#include "UI/StatRowWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"

void UStatRowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->HorizontalBox->AddChild(this->StatDescription);
	this->HorizontalBox->AddChild(this->Value);

	//this->Value->
}

void UStatRowWidget::SetToolTip(FText InToolTipText)
{
	this->StatDescription->SetToolTipText(InToolTipText);
	this->Value->SetToolTipText(InToolTipText);
}