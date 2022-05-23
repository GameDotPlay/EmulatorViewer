

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PopulateDetailsInterface.generated.h"

class UDetailsPopupContentWidget;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPopulateDetailsInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class EMULATORVIEWER_API IPopulateDetailsInterface
{
	GENERATED_BODY()

public:

	virtual void DetailsPopupInteract(UDetailsPopupContentWidget* ContentWidget) { return; }
};
