#include "Bomb.h"
#include "BombermanCharacter.h"
#include "Explosion.h"
#include "BlockBreakable.h"

#include <Components/SphereComponent.h>
#include <DrawDebugHelpers.h>

ABomb::ABomb()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetSphereRadius(35.f);
	SphereComponent->SetCollisionProfileName(FName("BombPosed"));
	RootComponent = SphereComponent;
}

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
	
	if ((x >= 0 && x <= 10 && y >= 0 && y <= 10) && MainBomber->GeneratedLevel) MainBomber->GeneratedLevel->matrix[x][y] = 0;

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

	if (IsHit)
	{
		float Distance = Hit.Distance;
		NbBlock = Distance / SizeBlock;

		ABlockBreakable* Block = Cast<ABlockBreakable>(Hit.GetActor());
		if (Block)
		{
			Block->Destroy();
			NbBlock++;
			int x = (GetActorLocation().X + 990 + Distance*Direction.X) / 180;
			int y = (GetActorLocation().Y + 990 + Distance*Direction.Y) / 180;
			if ((x >= 0 && x <= 10 && y >= 0 && y <= 10) && MainBomber->GeneratedLevel) MainBomber->GeneratedLevel->matrix[x][y] = 0;
		}
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

