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

	// Sets default values for this actor's properties
	ABlockBreakable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
