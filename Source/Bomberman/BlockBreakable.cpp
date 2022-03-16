#include "BlockBreakable.h"
#include "Extension.h"

#include <Components/BoxComponent.h>
#include <Math/UnrealMathUtility.h>

ABlockBreakable::ABlockBreakable()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = BoxComponent;

	bReplicates = true;
}

void ABlockBreakable::SpawnExtension()
{
	float SpawnExtension = FMath::RandRange(0, 1);
	if (SpawnExtension <= 0.6) return;

	int IndexExtension = FMath::RandRange(0, ListExtension.Num() - 1);

	FVector SpawnLocation = GetActorLocation();
	FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

	GetWorld()->SpawnActor<AExtension>(ListExtension[IndexExtension], SpawnTransform);
}

void ABlockBreakable::BeginPlay()
{
	Super::BeginPlay();
	
}