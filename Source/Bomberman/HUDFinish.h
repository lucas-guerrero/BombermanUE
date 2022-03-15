// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDFinish.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API UHUDFinish : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Resultat;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Compteur;

	UFUNCTION(BlueprintCallable)
	void SetResultat(FText Text);

	UFUNCTION(BlueprintCallable)
	void SetCompteur(float Time);

	virtual void NativeOnInitialized();
};
