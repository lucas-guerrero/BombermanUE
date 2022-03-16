#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PCLobby.generated.h"

UCLASS()
class BOMBERMAN_API APCLobby : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUD_Session_Multi> BP_HUD_SessionMenu;

	void ShowWaitMenu();

	UFUNCTION(BlueprintCallable)
	void HideWaitMenu();

	UFUNCTION(BlueprintCallable)
	void LaunchGame();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UHUD_Session_Multi* HUD_SessionMenu;
};
