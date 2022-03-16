#pragma once

#include "CoreMinimal.h"
#include "Extension.h"
#include "MoreBomb.generated.h"

UCLASS()
class BOMBERMAN_API AMoreBomb : public AExtension
{
	GENERATED_BODY()
	
public:
	virtual bool Effect(AActor* Main) override;
};
