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

	FString Level = TEXT(  "\
XXXXXXXXXXX\n\
X1 OOOOO 2X\n\
X XOXOXOX X\n\
XOOOOOOOOOX\n\
XOXOXOXOXOX\n\
XOOOOOOOOOX\n\
XOXOXOXOXOX\n\
XOOOOOOOOOX\n\
X XOXOXOX X\n\
X3 OOOOO 4X\n\
XXXXXXXXXXX");

	SizeLevels = 11;

	int x = SizeLevels;
	int y = SizeLevels;

	matrix.SetNum(x);
	for (int i = 0; i < x; i++) {
		matrix[i].Init(1, y);
	}

	--x;

	FString Left;
	FString Right;

	while (Level.Split(TEXT("\n"), &Left, &Right))
	{		
		GenerateRow(x, Left);

		--x;

		Level = Right;
		Left = TEXT("");
	}

	GenerateRow(x, Right);
}

void AGenerateLevel::GenerateRow(int x, FString Line)
{
	int y = 0;
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
