// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu_PC.h"
#include "HUD_Menu.h"
#include <Kismet/GameplayStatics.h>

void AMenu_PC::BeginPlay()
{
	Super::BeginPlay();

	if (BP_HUD_Menu != nullptr)
	{
		FString levelName = GetWorld()->GetMapName();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, levelName);

		if (levelName.Contains(FString("MainMenu")))
		{
			HUD_Menu = CreateWidget<UHUD_Menu>(this, BP_HUD_Menu);
			HUD_Menu->AddToViewport();
		}
	}
}

void AMenu_PC::ShowHUD_Menu()
{
	if (BP_HUD_Menu != nullptr)
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		HUD_Menu = CreateWidget<UHUD_Menu>(this, BP_HUD_Menu);
		HUD_Menu->AddToViewport();
	}
}

void AMenu_PC::HideHUD_Menu()
{
	if (BP_HUD_Menu != nullptr)
	{
		HUD_Menu->RemoveFromParent();
		HUD_Menu->Destruct();

		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

