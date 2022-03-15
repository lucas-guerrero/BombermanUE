// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PCGame.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API APCGame : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	class UHUDFinish* HUD_Finish;

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUDFinish> BP_HUDFinish;

	void ShowFinish(bool IsWinner);

	UFUNCTION(BlueprintCallable)
	void Finish(bool IsWinner);


};
