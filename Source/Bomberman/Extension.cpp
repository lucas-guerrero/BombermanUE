#include "Extension.h"

#include <Components/BoxComponent.h>

AExtension::AExtension()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetCollisionProfileName(FName("Extension"));
	BoxComponent->SetRelativeScale3D(FVector(1.8f, 1.8f, 1.8f));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AExtension::OnOverlapBegin);
	RootComponent = BoxComponent;
}

void AExtension::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AExtension::Effect(AActor* Main)
{
	return false;
}

void AExtension::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Effect(OtherActor)) Destroy();
}
