// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD_MultiMenu.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API UHUD_MultiMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* EditTextIp;

	virtual void NativeOnInitialized();

protected:
	UFUNCTION()
	void OnHostClick();

	UFUNCTION()
	void OnJoinClick();
};
