#include "MoreBomb.h"
#include "BombermanCharacter.h"

bool AMoreBomb::Effect(AActor* Main)
{
	ABombermanCharacter* Player = Cast<ABombermanCharacter>(Main);

	if (Player)
	{
		Player->AddBomb();
		return true;
	}
	
	return false;
}