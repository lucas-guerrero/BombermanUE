#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenerateLevel.h" 
#include "BombermanCharacter.generated.h"



UCLASS(config=Game)
class ABombermanCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABombermanCharacter();

	// the class used to spawn a patate object
	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = Bomb)
	TSubclassOf<class ABomb> BombClass;

	// number of bomb
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	int NbBombPossed;

	// number of Cell of the bomb explosed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	int NbCellExplosed;

	// get the generatedLevel and the matrix level
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
	AGenerateLevel* GeneratedLevel;


protected:
	void MoveForward(float Value);

	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable, Category="Bomb")
	void TakeBomb();

	UFUNCTION(BlueprintCallable, Category = "AI")
	FVector GetFleeLocation(FVector BombLocation);

	UFUNCTION(BlueprintCallable, Category = "AI")
	FVector GetNearestBomb();

	UFUNCTION(BlueprintCallable, Category = "AI")
	bool FleeOrSeek();

	void GetListMovementPossible(std::tuple<int, int> depart, TArray<std::tuple<int, int>> &liste);

	int Manhattan(int x1, int y1, int x2, int y2);

	void SpawnBomb(FTransform Transform);

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

public:
	void AddBomb();
	void RemoveBomb();

	void AddExplosion();
	void RemoveExplosion();
};

