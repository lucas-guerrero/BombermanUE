#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenerateLevel.generated.h"

UCLASS()
class BOMBERMAN_API AGenerateLevel : public AActor
{
	GENERATED_BODY()
	
public:
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

	UFUNCTION(BlueprintCallable)
	void GenerateMap();

	TArray<TArray<int>> matrix;

protected:
	virtual void BeginPlay() override;

	void GenerateRow(int x, FString Line);

	void GenerateWall(int x, int y);

	void GenerateBreak(int x, int y);

	void GenerateCamera();
};
