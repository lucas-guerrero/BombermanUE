// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "BombermanCharacter.h"
#include "Explosion.h"

#include <Components/SphereComponent.h>
#include <DrawDebugHelpers.h>

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetSphereRadius(35.f);
	//SphereComponent->SetCollisionProfileName(FName("Patate"));
	//SphereComponent->SetSimulatePhysics(false);
	SphereComponent->SetNotifyRigidBodyCollision(false);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABomb::OnOverlapEnd);
	RootComponent = SphereComponent;
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(1.f);
}

void ABomb::Destroyed()
{
	if (MainBomber != nullptr)
	{
		MainBomber->NbBombPossed++;
		Explose();
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Bomb !!!");
	}
}

void ABomb::ExploseDirection(FVector Direction)
{
	float Reach = 500.f;
	FVector End = GetActorLocation() + Direction * Reach;
	FVector Begin = GetActorLocation();

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		Begin,
		End,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
		TraceParams
	);

	DrawDebugLine(GetWorld(), Begin, End, FColor::Red, false, 1.f);

	/*
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit != nullptr)
	{
		ActorHit->Destroy();
	}
	*/

	for (int i = 0; i < 4; ++i)
	{
		FVector Spawn = (Direction * i) + GetActorLocation();
		FTransform Transform = GetActorTransform();
		Transform.SetTranslation(Spawn);

		AExplosion* Explo = GetWorld()->SpawnActorDeferred<AExplosion>(ExplosionClass, Transform);
		Explo->FinishSpawning(Transform);
	}
}

void ABomb::Explose()
{
	ExploseDirection(FVector::RightVector);
	ExploseDirection(FVector::LeftVector);
	ExploseDirection(FVector::ForwardVector);
	ExploseDirection(FVector::BackwardVector);
}

void ABomb::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Change !!");
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

