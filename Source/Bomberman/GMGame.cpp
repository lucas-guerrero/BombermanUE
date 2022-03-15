// Fill out your copyright notice in the Description page of Project Settings.


#include "GMGame.h"
#include "GSGame.h"

AGMGame::AGMGame()
{
	NbPlayerAlive = 4;
}

void AGMGame::PlayerDead()
{
	--NbPlayerAlive;
	if (NbPlayerAlive <= 1)
	{
		AGSGame *GameStat = GetGameState<AGSGame>();

		if(GameStat) GameStat->Finish();
	}
}
