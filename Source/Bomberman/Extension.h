// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Extension.generated.h"

UCLASS()
class BOMBERMAN_API AExtension : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExtension();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Explosion, meta = (AllowPrivateAccess = "true"));
	class UBoxComponent* BoxComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool Effect(AActor* Main);
};
