// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GSGame.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API AGSGame : public AGameState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated, EditAnywhere)
	int NbPlayer;

	UFUNCTION(BlueprintCallable)
	void SetNbPlayer(int NewNbPlayer);

	UFUNCTION(BlueprintCallable)
	int GetNbPlayer();

	//virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;
};
