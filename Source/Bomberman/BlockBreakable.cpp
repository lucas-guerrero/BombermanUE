// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockBreakable.h"

#include <Components/BoxComponent.h>

// Sets default values
ABlockBreakable::ABlockBreakable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = BoxComponent;
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

