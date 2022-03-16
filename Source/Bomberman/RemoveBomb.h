#pragma once

#include "CoreMinimal.h"
#include "Extension.h"
#include "RemoveBomb.generated.h"

UCLASS()
class BOMBERMAN_API ARemoveBomb : public AExtension
{
	GENERATED_BODY()
	
public:
	virtual bool Effect(AActor* Main) override;
};
