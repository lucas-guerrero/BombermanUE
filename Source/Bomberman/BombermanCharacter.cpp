// Copyright Epic Games, Inc. All Rights Reserved.

#include "BombermanCharacter.h"
#include "Bomb.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include <TimerManager.h>

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

//////////////////////////////////////////////////////////////////////////
// Input

void ABombermanCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Bomb", IE_Pressed, this, &ABombermanCharacter::TakeBomb);

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

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ABombermanCharacter::SpawnBomb, Tranform);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.25f, false);
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
	if (NbCellExplosed <= 1) return;
	--NbCellExplosed;
}