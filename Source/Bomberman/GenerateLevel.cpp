#include "GenerateLevel.h"
#include "Wall.h"
#include "BlockBreakable.h"
#include "BombermanCharacter.h"
#include "GSGame.h"

#include <fstream>
#include <string>
#include <Misc/Paths.h>
#include <EngineUtils.h>
#include <Kismet/GameplayStatics.h>

AGenerateLevel::AGenerateLevel()
{
	PrimaryActorTick.bCanEverTick = false;

	UnitBlock = 360/2;
}

void AGenerateLevel::GenerateMap()
{
	GenerateCamera();

	std::string NameFile = TCHAR_TO_UTF8(*FPaths::ProjectDir());
	NameFile = NameFile + "/Content/Levels/lvl1.txt";

	std::ifstream File(NameFile);
	if (File.is_open())
	{
		std::string Line;

		File >> Line >> SizeLevels;

		int x = SizeLevels;
		int y = SizeLevels;

		matrix.SetNum(x);
		for (int i = 0; i < x; i++) {
			matrix[i].Init(1, y);
		}

		while (std::getline(File, Line))
		{
			y = 0;
			for (char c : Line)
			{
				switch (c)
				{
				case 'X':
					GenerateWall(x, y);
					matrix[x][y] = 1;
					break;
				case 'O':
					GenerateBreak(x, y);
					matrix[x][y] = 2;
					break;
				default:
					matrix[x][y] = 0;
					break;
				}
				y++;
			}
			x--;
		}
	}

	File.close();
}

void AGenerateLevel::BeginPlay()
{
	Super::BeginPlay();
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

void AGenerateLevel::GenerateCamera()
{
	APlayerCameraManager* PCM = UGameplayStatics::GetPlayerCameraManager(this, 0);
	if (PCM)
	{
		PCM->SetActorLocation(FVector(30.f, 30.f, 100.f));
		PCM->SetActorRotation(FVector(0.f, -90.f, 0.f).Rotation());
	}
}
