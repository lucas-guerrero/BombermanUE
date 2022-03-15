// Fill out your copyright notice in the Description page of Project Settings.


#include "GSGame.h"

#include <Net/UnrealNetwork.h>

void AGSGame::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AGSGame, NbPlayer);
    DOREPLIFETIME(AGSGame, IsFinish);
}

void AGSGame::SetNbPlayer(int NewNbPlayer)
{
    NbPlayer = NewNbPlayer;
}

int AGSGame::GetNbPlayer()
{
    return NbPlayer;
}

void AGSGame::Finish()
{
    IsFinish = true;
}

void AGSGame::SetIsFinish()
{
    IsFinish = false;
}

bool AGSGame::CanFinish()
{
    return IsFinish;
}