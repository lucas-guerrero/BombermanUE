// Copyright Epic Games, Inc. All Rights Reserved.

#include "BombermanCharacter.h"
#include "Bomb.h"
#include "GameCamera.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include <TimerManager.h>
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// ABombermanCharacter

ABombermanCharacter::ABombermanCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	NbBombPossed = 1;

	NbCellExplosed = 2;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
}

// Called when the game starts or when spawned
void ABombermanCharacter::BeginPlay()
{
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABombermanCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Bomb", IE_Pressed, this, &ABombermanCharacter::TakeBomb);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABombermanCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABombermanCharacter::MoveRight);
}

void ABombermanCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABombermanCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ABombermanCharacter::TakeBomb()
{
	if (NbBombPossed <= 0 || BombClass == nullptr) return;
	NbBombPossed--;

	FVector Location = GetActorLocation();
	Location.Z -= 90.f;
	FTransform Tranform(GetActorRotation(), Location, GetActorScale());

	SpawnBomb(Tranform);
}



FVector ABombermanCharacter::GetFleeLocation(FVector BombLocation)
{
	int x1, y1;
	int MaxDist = 0;
	int posX = 0, posY = 0;

	x1 = BombLocation.X/360;
	y1 = BombLocation.Y/360;
	for(int x2 = 0; x2 < matrix.Num() ; ++x2)
	{
		for (int y2 = 0; y2 < matrix[x2].Num() ; ++y2)
		{
			int distance = Manhattan(x1, y1, x2, y2);
			if (distance > MaxDist)
			{
				MaxDist = distance;
				posX = x2*360;
				posY = y2*360;
			}
		}
	}

	return FVector(posX,posY,GetActorLocation().Z);
}

void ABombermanCharacter::GetTerrainMatrix()
{
	return;
}

void  ABombermanCharacter::SetTerrainMatrix()
{
	return;
}

int ABombermanCharacter::Manhattan(int x1, int y1, int x2, int y2)
{
	int x_dif, y_dif;

	x_dif = x2 - x1;
	y_dif = y2 - y1;
	if (x_dif < 0)
		x_dif = -x_dif;
	if (y_dif < 0)
		y_dif = -y_dif;
	return  x_dif + y_dif;
}


void ABombermanCharacter::SpawnBomb(FTransform Transform)
{
	ABomb* Bomb = GetWorld()->SpawnActorDeferred<ABomb>(BombClass, Transform);
	Bomb->SetMainBomber(this);
	Bomb->FinishSpawning(Transform);
}

void ABombermanCharacter::AddBomb()
{
	++NbBombPossed;
}

void ABombermanCharacter::RemoveBomb()
{
	if (NbBombPossed <= 1) return;
	--NbBombPossed;
}

void ABombermanCharacter::AddExplosion()
{
	++NbCellExplosed;
}

void ABombermanCharacter::RemoveExplosion()
{
	if (NbCellExplosed <= 2) return;
	--NbCellExplosed;
}