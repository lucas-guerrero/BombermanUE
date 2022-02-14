// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenerateLevel.generated.h"

UCLASS()
class BOMBERMAN_API AGenerateLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerateLevel();

	UPROPERTY(VisibleAnywhere)
	float UnitBlock;

	int SizeLevels;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly)
	TSubclassOf<class AWall> WallClass;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly)
	TSubclassOf<class ABlockBreakable> BreakClass;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly)
	TSubclassOf<class ABombermanCharacter> PlayerClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GenerateWall(int x, int y);

	void GenerateBreak(int x, int y);

	void GeneratePlayer(int x, int y, char c);
};
