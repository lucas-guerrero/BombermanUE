// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class BOMBERMAN_API ABomb : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bomb, meta = (AllowPrivateAccess = "true"));
	class USphereComponent* SphereComponent;

	class ABombermanCharacter* MainBomber;

public:
	ABomb();

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = Bomb)
	TSubclassOf<class AExplosion> ExplosionClass;

	UPROPERTY(EditAnywhere, Category = Bomb)
	bool Explode = true;

protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	void ExploseDirection(FVector Direction);

public:

	void Explose();

	FORCEINLINE void SetMainBomber(class ABombermanCharacter* MainBomberman)
	{
		MainBomber = MainBomberman;
	}
};
