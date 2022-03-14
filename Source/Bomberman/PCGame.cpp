// Fill out your copyright notice in the Description page of Project Settings.


#include "PCGame.h"

#include <Blueprint/WidgetLayoutLibrary.h>

void APCGame::BeginPlay()
{
	Super::BeginPlay();

	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}