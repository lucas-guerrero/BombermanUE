// Fill out your copyright notice in the Description page of Project Settings.


#include "GSGame.h"

/*
void AGSGame::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    //DOREPLIFETIME(AGSGame, NbPlayer);
}
*/

void AGSGame::SetNbPlayer(int NewNbPlayer)
{
    NbPlayer = NewNbPlayer;
}

int AGSGame::GetNbPlayer()
{
    return NbPlayer;
}