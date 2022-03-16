#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD_Menu.generated.h"

UCLASS()
class BOMBERMAN_API UHUD_Menu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* SoloButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MultiButton;

	virtual void NativeOnInitialized();

protected:
	UFUNCTION()
	void OnPlayClick();

	UFUNCTION()
	void OnMultiClick();

	UFUNCTION()
	void OnQuitClick();

};
