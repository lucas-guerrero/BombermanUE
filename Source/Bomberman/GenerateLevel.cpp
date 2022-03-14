// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerateLevel.h"
#include "Wall.h"
#include "BlockBreakable.h"
#include "BombermanCharacter.h"

#include <fstream>
#include <string>
#include <Misc/Paths.h>
#include <EngineUtils.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AGenerateLevel::AGenerateLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UnitBlock = 360/2;
}

// Called when the game starts or when spawned
void AGenerateLevel::BeginPlay()
{
	Super::BeginPlay();

	//360 unit for 1 block
	// 9 block per rows / columns
	/*
	int NbBlock = 7;
	float SizeLevels = NbBlock * UnitBlock / 2;
	*/

	GenerateCamera();

	if (HasAuthority()) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Authority"));

	std::string NameFile = TCHAR_TO_UTF8(*FPaths::ProjectDir());
	NameFile = NameFile + "/Content/Levels/lvl1.txt";

	std::ifstream File(NameFile);
	if (File.is_open())
	{
		std::string Line;

		File >> Line >> SizeLevels;

		int x = SizeLevels;
		int y = SizeLevels;

		while (std::getline(File, Line))
		{
			y = 0;
			for (char c : Line)
			{
				switch (c)
				{
				case 'X':
					GenerateWall(x, y);
					break;
				case 'O':
					GenerateBreak(x, y);
					break;
				default:
					GeneratePlayer(x, y, c);
					break;
				}
				y++;
			}
			x--;
		}
	}

	File.close();
}

void AGenerateLevel::GenerateWall(int x, int y)
{
	if (WallClass)
	{
		float Decalage = SizeLevels/2 * UnitBlock;

		FVector SpawnLocation = FVector(x*UnitBlock - Decalage, y*UnitBlock - Decalage, 0.f);
		FTransform SpawnTransform(GetActorRotation(), SpawnLocation);
		GetWorld()->SpawnActor<AWall>(WallClass, SpawnTransform);
	}
}

void AGenerateLevel::GenerateBreak(int x, int y)
{
	if (BreakClass)
	{
		float Decalage = SizeLevels/2 * UnitBlock;

		FVector SpawnLocation = FVector(x * UnitBlock - Decalage, y * UnitBlock - Decalage, 0.f);
		FTransform SpawnTransform(GetActorRotation(), SpawnLocation);
		GetWorld()->SpawnActor<ABlockBreakable>(BreakClass, SpawnTransform);
	}
}

void AGenerateLevel::GeneratePlayer(int x, int y, char c)
{
	if (c != ' ')
	{
		// TODO Traitement player Multi ou IA
		float Decalage = SizeLevels / 2 * UnitBlock;

		FVector SpawnLocation = FVector(x * UnitBlock - Decalage, y * UnitBlock - Decalage, 0.f);
		FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

		if (c == '1')
		{
			UGameplayStatics::GetGameState(GetWorld());
			APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
			if (PC)
			{
				APawn* Player = PC->GetPawn();
				GEngine->AddOnScreenDebugMessage(-1, 500.f, FColor::Red, Player->GetName());

				Player->SetActorLocation(SpawnLocation);
			}
		}
		else
		{
			ABombermanCharacter* Player = GetWorld()->SpawnActorDeferred<ABombermanCharacter>(PlayerClass, SpawnTransform);
			Player->FinishSpawning(SpawnTransform);
		}

		/*
		for (TActorIterator<ABombermanCharacter> ActorItr(GetWorld(), ABombermanCharacter::StaticClass()); ActorItr; ++ActorItr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 500.f, FColor::Red, ActorItr->GetName());
		}
		*/
		/*
		for (size_t i = 0; i < 4; i++)
		{
			APlayerController* PC = UGameplayStatics::GetPlayerController(this, i);
			if (PC)
			{
				APawn* Player = PC->GetPawn();
				GEngine->AddOnScreenDebugMessage(-1, 500.f, FColor::Red, Player->GetName());
			}
			
		}
		*/
		
	}
}

void AGenerateLevel::GenerateCamera()
{

	APlayerCameraManager* PCM = UGameplayStatics::GetPlayerCameraManager(this, 0);
	if (PCM)
	{
		PCM->SetActorLocation(FVector(30.f, 30.f, 100.f));
		PCM->SetActorRotation(FVector(0.f, -90.f, 0.f).Rotation());

		GEngine->AddOnScreenDebugMessage(-1, 500.f, FColor::Red, "CAMERA : " + PCM->GetCameraLocation().ToString());
	}
}
