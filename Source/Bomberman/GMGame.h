// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GMGame.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API AGMGame : public AGameMode
{
	GENERATED_BODY()

private:
	int NbPlayerAlive;
	
public:
	AGMGame();

	UFUNCTION(BlueprintCallable)
	void PlayerDead();
};
