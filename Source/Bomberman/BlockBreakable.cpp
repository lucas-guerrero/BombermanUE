// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockBreakable.h"
#include "Extension.h"

#include <Components/BoxComponent.h>
#include <Math/UnrealMathUtility.h>

// Sets default values
ABlockBreakable::ABlockBreakable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = BoxComponent;

	bReplicates = true;
}

void ABlockBreakable::Destroyed()
{
	/*
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ABlockBreakable::SpawnExtension);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.75f, false);
	*/

	SpawnExtension();
}

void ABlockBreakable::SpawnExtension()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Generate !!!"));
	float SpawnExtension = FMath::RandRange(0, 1);
	if (SpawnExtension <= 0.6) return;

	int IndexExtension = FMath::RandRange(0, ListExtension.Num() - 1);

	FVector SpawnLocation = GetActorLocation();
	FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

	GetWorld()->SpawnActor<AExtension>(ListExtension[IndexExtension], SpawnTransform);
}

// Called when the game starts or when spawned
void ABlockBreakable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlockBreakable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

