
#include "UI/StatRow.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"

void UStatRow::NativeConstruct()
{
	Super::NativeConstruct();

	this->HorizontalBox->AddChild(this->StatDescription);
	this->HorizontalBox->AddChild(this->Value);

	this->Value->
}

void UStatRow::SetToolTip(FText InToolTipText)
{
	this->StatDescription->SetToolTipText(InToolTipText);
	this->Value->SetToolTipText(InToolTipText);
}