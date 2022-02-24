// Fill out your copyright notice in the Description page of Project Settings.


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