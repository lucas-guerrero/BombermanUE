// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Extension.h"
#include "MoreExplosion.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API AMoreExplosion : public AExtension
{
	GENERATED_BODY()

public:
	virtual bool Effect(AActor* Main) override;
};
