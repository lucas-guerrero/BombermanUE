#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD_MultiMenu.generated.h"

UCLASS()
class BOMBERMAN_API UHUD_MultiMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeOnInitialized();
};
