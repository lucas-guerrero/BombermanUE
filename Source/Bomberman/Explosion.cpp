#include "Explosion.h"
#include "BombermanCharacter.h"
#include "Bomb.h"

#include <Components/BoxComponent.h>

AExplosion::AExplosion()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetCollisionProfileName(FName("Explosion"));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AExplosion::OnOverlapBegin);
	RootComponent = BoxComponent;
}

void AExplosion::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	OtherActor->Destroy();
}

void AExplosion::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(lifeSpan);
}

