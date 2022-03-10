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

	void TakeBomb();

	void SpawnBomb(FTransform Transform);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	void AddBomb();
	void RemoveBomb();

	void AddExplosion();
	void RemoveExplosion();
};

