// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD_Session_Multi.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API UHUD_Session_Multi : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* LaunchButton;

	virtual void NativeOnInitialized();

	void NotAutority();
};
