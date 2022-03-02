// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD_Menu.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API UHUD_Menu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		class UButton* B_Quitter;
	UPROPERTY(meta = (BindWidget))
		class UButton* B_Jouer;

	virtual void NativeOnInitialized();

protected:
	UFUNCTION()
		void OnJouerClick();

	UFUNCTION()
		void OnQuitterClick();

};
