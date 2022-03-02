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

	void ShowHUD_Menu();
	void HideHUD_Menu();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		class UHUD_Menu* HUD_Menu;
};
