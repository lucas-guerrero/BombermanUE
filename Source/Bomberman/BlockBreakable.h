// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockBreakable.generated.h"

UCLASS()
class BOMBERMAN_API ABlockBreakable : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Block, meta = (AllowPrivateAccess = "true"));
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = Bomb);
	TArray<TSubclassOf<class AExtension>> ListExtension;

	ABlockBreakable();

	UFUNCTION(BlueprintCallable)
	void SpawnExtension();

protected:
	virtual void BeginPlay() override;

};
