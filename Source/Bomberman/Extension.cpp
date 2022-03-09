// Fill out your copyright notice in the Description page of Project Settings.


#include "Extension.h"

#include <Components/BoxComponent.h>

// Sets default values
AExtension::AExtension()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetCollisionProfileName(FName("Extension"));
	BoxComponent->SetRelativeScale3D(FVector(1.8f, 1.8f, 1.8f));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AExtension::OnOverlapBegin);
	RootComponent = BoxComponent;
}

// Called when the game starts or when spawned
void AExtension::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExtension::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AExtension::Effect(AActor* Main)
{
	return false;
}


void AExtension::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Effect(OtherActor)) Destroy();
}
