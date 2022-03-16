#include "MoreExplosion.h"

#include "BombermanCharacter.h"

bool AMoreExplosion::Effect(AActor* Main)
{
	ABombermanCharacter* Player = Cast<ABombermanCharacter>(Main);

	if (Player)
	{
		Player->AddExplosion();
		return true;
	}

	return false;
}