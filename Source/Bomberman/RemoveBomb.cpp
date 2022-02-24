// Fill out your copyright notice in the Description page of Project Settings.


#include "RemoveBomb.h"
#include "BombermanCharacter.h"

bool ARemoveBomb::Effect(AActor* Main)
{
	ABombermanCharacter* Player = Cast<ABombermanCharacter>(Main);

	if (Player)
	{
		Player->RemoveBomb();
		return true;
	}

	return false;
}