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
	SphereComponent->SetCollisionProfileName(FName("BombPosed"));
	RootComponent = SphereComponent;
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();

	if (Explode) SetLifeSpan(2.f);
}

void ABomb::Destroyed()
{
	if (!MainBomber) return;
	int x = (GetActorLocation().X + 990) / 180;
	int y = (GetActorLocation().Y + 990) / 180;
	if (x >= 0 && x <= 10 && y >= 0 && y <= 10)
	{
		if(MainBomber->GeneratedLevel)
		MainBomber->GeneratedLevel->matrix[x][y] = 0;
	}
	
	MainBomber->NbBombPossed++;
	Explose();
}

void ABomb::ExploseDirection(FVector Direction)
{
	float SizeBlock = 200;

	int bombeX = (GetActorLocation().X + 990) / 180;
	int bombeY = (GetActorLocation().Y + 990) / 180;

	int NbBlock = MainBomber->NbCellExplosed;
	float Reach = NbBlock * SizeBlock;
	FVector End = GetActorLocation() + Direction * Reach;
	FVector Begin = GetActorLocation();

	FHitResult Hit;
	ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
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
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "HIT");
		//FHitResult Hit = Hits[0];
		//DrawDebugLine(GetWorld(), Begin, Hit.GetActor()->GetActorLocation(), FColor::Red, false, 0.5f);

		float Distance = Hit.Distance;
		NbBlock = Distance / SizeBlock;

		ABlockBreakable* Block = Cast<ABlockBreakable>(Hit.GetActor());
		if (Block)
		{
			Block->Destroy();
			NbBlock++;
			int x = (GetActorLocation().X + 990 + Distance*Direction.X) / 180;
			int y = (GetActorLocation().Y + 990 + Distance*Direction.Y) / 180;
			if (x >= 0 && x <= 10 && y >= 0 && y <= 10)
			{
				if (MainBomber->GeneratedLevel)
				MainBomber->GeneratedLevel->matrix[x][y] = 0;
			}
		}
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("NBBlock: %d"), NbBlock));
	}
	
	
	// 1 Block = 4*50
	for (int i = 0; i < NbBlock*4; ++i)
	{
		FVector SpawnLocation = (Direction * i * 50) + GetActorLocation();
		FTransform SpawnTransform(GetActorRotation(), SpawnLocation);
		AExplosion* Explo = GetWorld()->SpawnActor<AExplosion>(ExplosionClass, SpawnTransform);
	}
	
	//MainBomber->GeneratedLevel->matrix[x][y] = 0;
}

void ABomb::Explose()
{
	ExploseDirection(FVector::RightVector);
	ExploseDirection(FVector::LeftVector);
	ExploseDirection(FVector::ForwardVector);
	ExploseDirection(FVector::BackwardVector);
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

