// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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


protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable, Category="Bomb")
	void TakeBomb();

	//USTRUCT(BlueprintType)
	//	struct SEED_API matrix
	//{
	//	GENERATED_USTRUCT_Body()
	//public:
	//	TArray<int> Value;
	//};
	//UCLASS(ClassGroup = (Custom), eta = (BlueprintSpawnableComponent))
	//	class SEED_APE UPassiveComponent : public UActorComponent, public ILifeValueState
	//	SetInterface
	//{
	//	GENERATED_BODY()
	//public:
	//	UPassiveComponent();
	//private:
	//	UPROPERTY(EditAnywhere, BluprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//		TMap<EPassiveType, FPassiveData> PassiveList;
	//};


	TArray<TArray<int>> matrix;


	UFUNCTION(BlueprintCallable, Category = "Bomb")
	FVector GetFleeLocation(FVector BombLocation);
	
	void GetTerrainMatrix();

	void SetTerrainMatrix();

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

