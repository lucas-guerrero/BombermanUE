// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosion.h"
#include "BombermanCharacter.h"
#include "Bomb.h"

#include <Components/BoxComponent.h>

// Sets default values
AExplosion::AExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AExplosion::OnOverlapBegin);
	RootComponent = BoxComponent;
}

void AExplosion::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ABombermanCharacter>(OtherActor) != nullptr)
	{
		OtherActor->Destroy();
	}
	else if (Cast<ABomb>(OtherActor) != nullptr)
	{
		ABomb* Bomb = Cast<ABomb>(OtherActor);
		Bomb->Explose();
	}
}

// Called when the game starts or when spawned
void AExplosion::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(2.f);
}

// Called every frame
void AExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

