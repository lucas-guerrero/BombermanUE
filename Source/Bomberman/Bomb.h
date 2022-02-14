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
	// Sets default values for this actor's properties
	ABomb();

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = Bomb)
	TSubclassOf<class AExplosion> ExplosionClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	void ExploseDirection(FVector Direction);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Explose();

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FORCEINLINE void SetMainBomber(class ABombermanCharacter* MainBomberman)
	{
		MainBomber = MainBomberman;
	}
};
