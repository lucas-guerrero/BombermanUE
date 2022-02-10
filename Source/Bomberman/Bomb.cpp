// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "BombermanCharacter.h"
#include "Explosion.h"
#include "BlockBreakable.h"

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
	SetLifeSpan(2.f);
}

void ABomb::Destroyed()
{
	if (MainBomber != nullptr)
	{
		MainBomber->NbBombPossed++;

		Explose();

		//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, "Bomb !!!");
	}
}

void ABomb::ExploseDirection(FVector Direction)
{
	float SizeBlock = 4 * 50;
	int NbBlock = MainBomber->NbCellExplosed + 2;
	float Reach = NbBlock * SizeBlock;
	FVector End = GetActorLocation() + Direction * Reach;
	FVector Begin = GetActorLocation();

	FHitResult Hit;
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel2;
	FCollisionQueryParams QueryParam;
	QueryParam.AddIgnoredActor(this);

	bool IsHit = GetWorld()->LineTraceSingleByChannel(
		OUT Hit,
		Begin,
		End,
		Channel,
		QueryParam
	);

	//DrawDebugLine(GetWorld(), Begin, End, FColor::Red, false, 0.5f);

	if (IsHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "HIT");
		//FHitResult Hit = Hits[0];
		DrawDebugLine(GetWorld(), Begin, Hit.GetActor()->GetActorLocation(), FColor::Red, false, 0.5f);

		ABlockBreakable* Block = Cast<ABlockBreakable>(Hit.GetActor());
		if (Block)
		{
			Block->Destroy();
		}

		float Distance = Hit.Distance;
		NbBlock = Distance / SizeBlock;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("NBBlock: %d"), NbBlock));
	}
	
	
	// 1 Block = 4*50
	for (int i = 0; i < NbBlock*4; ++i)
	{
		FVector SpawnLocation = (Direction * i * 50) + GetActorLocation();
		FTransform SpawnTransform(GetActorRotation(), SpawnLocation);
		AExplosion* Explo = GetWorld()->SpawnActor<AExplosion>(ExplosionClass, SpawnTransform);
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

