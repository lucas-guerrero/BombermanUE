// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Menu_PC.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API AMenu_PC : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUD_Menu> BP_HUD_Menu;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUD_MultiMenu> BP_HUD_MultiMenu;

	void ShowMenu();
	void HideMenu();

	void ShowMultiMenu();
	void HideMultiMenu();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UHUD_Menu* HUD_Menu;

	UPROPERTY()
	class UHUD_MultiMenu* HUD_MultiMenu;
};
