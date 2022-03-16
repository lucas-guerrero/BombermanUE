#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Explosion.generated.h"

UCLASS()
class BOMBERMAN_API AExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Explosion, meta = (AllowPrivateAccess = "true"));
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Explosion, meta = (AllowPrivateAccess = "true"));
	float lifeSpan = 0.5f;
	
	AExplosion();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
