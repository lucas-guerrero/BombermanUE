// Fill out your copyright notice in the Description page of Project Settings.


#include "RemoveExplosion.h"
#include "BombermanCharacter.h"

bool ARemoveExplosion::Effect(AActor* Main)
{
	ABombermanCharacter* Player = Cast<ABombermanCharacter>(Main);

	if (Player)
	{
		Player->RemoveExplosion();
		return true;
	}

	return false;
}