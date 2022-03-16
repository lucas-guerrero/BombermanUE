#include "BombermanCharacter.h"
#include "BlockBreakable.h"
#include "Bomb.h"
#include "GameCamera.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

ABombermanCharacter::ABombermanCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	NbBombPossed = 1;

	NbCellExplosed = 2;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ABombermanCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABombermanCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABombermanCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABombermanCharacter::MoveRight);
}

void ABombermanCharacter::MoveForward(float Value)
{
	if ( Controller && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABombermanCharacter::MoveRight(float Value)
{
	if ( Controller && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}


void ABombermanCharacter::TakeBomb()
{
	if (NbBombPossed <= 0 || !BombClass) return;
	NbBombPossed--;

	FVector Location = GetActorLocation();
	Location.Z -= 90.f;
	FTransform Tranform(GetActorRotation(), Location, GetActorScale());

	int x = (GetActorLocation().X + 990) / 180;
	int y = (GetActorLocation().Y + 990) / 180;
	if ((x >= 0 && x <= 10 && y >= 0 && y <= 10) && GeneratedLevel) GeneratedLevel->matrix[x][y] = 3;

	SpawnBomb(Tranform);
}

bool ABombermanCharacter::FleeOrSeek()
{
	if (!GeneratedLevel) return true;

	int x1 = (GetActorLocation().X + 990) / 180;
	int y1 = (GetActorLocation().Y + 990) / 180;
	TArray<TArray<int>> mat = GeneratedLevel->matrix;
	for (int x = 0 ; x < mat.Num() ; ++x)
	{
		for (int y = 0; y < mat[x].Num(); ++y)
		{
			if (mat[x][y]==3 && Manhattan(x1, y1, x, y) <= 4)
			{
				return false;
			}
		}
	}
	return true;
}

FVector ABombermanCharacter::GetNearestBomb()
{
	if (!GeneratedLevel) return GetActorLocation();

	int x1 = (GetActorLocation().X + 990) / 180;
	int y1 = (GetActorLocation().Y + 990) / 180;
	TArray<TArray<int>> mat = GeneratedLevel->matrix;
	for (int x = 0; x < mat.Num(); ++x)
	{
		for (int y = 0; y < mat[x].Num(); ++y)
		{
			if (mat[x][y] == 3 && Manhattan(x1, y1, x, y) <= 3)
			{
				int posX = (x * 180 - 900);
				int posY = (y * 180 - 900);
				return FVector(posX, posY,GetActorLocation().Z);
			}
		}
	}
	return GetActorLocation();
}

FVector ABombermanCharacter::GetFleeLocation(FVector BombLocation)
{

	int x1 = (BombLocation.X + 990) / 180;
	int y1 = (BombLocation.Y + 990) / 180;

	TArray<std::tuple<int, int>> list;
	if (!GeneratedLevel) return GetActorLocation();
	
	GetListMovementPossible({ x1,y1 }, list);

	int MaxDist = 0;
	int posX = 0, posY = 0;


	for (std::tuple<int, int> tup : list)
	{

		int x2 = std::get<0>(tup);
		int y2 = std::get<1>(tup);
		int distance = Manhattan(x1, y1, x2, y2);
		if (distance > MaxDist)
		{
			MaxDist = distance;
			posX = x2;
			posY = y2;
		}

	}

	int X = (posX * 180 - 900);
	int Y = (posY * 180 - 900);

	return FVector(X, Y, GetActorLocation().Z);
	
}

void ABombermanCharacter::GetListMovementPossible(std::tuple<int,int> depart, TArray<std::tuple<int, int>> &liste)
{
	int x = std::get<0>(depart);
	int y = std::get<1>(depart);
	if (x >= 0 && x <= 10 && y >= 0 && y <= 10)
	{
		if (x - 1 >= 0)
		{
			if ( GeneratedLevel->matrix[x-1][y] == 0 && !liste.Contains(std::make_tuple(x - 1, y)))
			{
				liste.Add({ x - 1,y });
				GetListMovementPossible({ x - 1,y }, liste);
			}
		}
		if(x+1 <= 10)
		{
			if(GeneratedLevel->matrix[x+1][y] == 0 && !liste.Contains(std::make_tuple(x + 1,y )))
			{
				liste.Add({ x + 1,y });
				GetListMovementPossible({ x + 1,y }, liste);
			}
		}
		if(y-1 >= 0)
		{
			if (GeneratedLevel->matrix[x][y-1] == 0 && !liste.Contains(std::make_tuple(x , y - 1)))
			{
				liste.Add({ x ,y - 1 });
				GetListMovementPossible({ x ,y - 1 }, liste);
			}
		}
		if(y+1 <= 10)
		{
			if (GeneratedLevel->matrix[x][y+1] == 0 && !liste.Contains(std::make_tuple(x, y + 1)))
			{
				liste.Add({ x,y + 1 });
				GetListMovementPossible({ x,y + 1 }, liste);
			}
		}
	}
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