
#include "UI/InteractionModeLabelWidget.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"

void UInteractionModeLabelWidget::SetInteractionModeText(FText InteractionModeText)
{
	this->InteractionModeLabel->SetText(InteractionModeText);
}

void UInteractionModeLabelWidget::NativeConstruct()
{
	Super::NativeConstruct();
}