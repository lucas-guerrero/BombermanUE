#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Extension.generated.h"

UCLASS()
class BOMBERMAN_API AExtension : public AActor
{
	GENERATED_BODY()
	
public:
	AExtension();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Explosion, meta = (AllowPrivateAccess = "true"));
	class UBoxComponent* BoxComponent;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual bool Effect(AActor* Main);
};
