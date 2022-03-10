// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu_PC.h"
#include "HUD_Menu.h"
#include "HUD_MultiMenu.h"

#include <Kismet/GameplayStatics.h>

void AMenu_PC::BeginPlay()
{
	Super::BeginPlay();

	FString levelName = GetWorld()->GetMapName();

	if (levelName.Contains(FString("MainMenu"))) ShowMenu();
}

void AMenu_PC::ShowMenu()
{
	if (!BP_HUD_Menu) return;

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	HUD_Menu = CreateWidget<UHUD_Menu>(this, BP_HUD_Menu);
	HUD_Menu->AddToViewport();
}

void AMenu_PC::ShowMultiMenu()
{
	if (!BP_HUD_MultiMenu) return;

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	HUD_MultiMenu = CreateWidget<UHUD_MultiMenu>(this, BP_HUD_MultiMenu);
	HUD_MultiMenu->AddToViewport();
}

void AMenu_PC::HideMenu()
{
	if (!HUD_Menu) return;

	HUD_Menu->RemoveFromParent();
	HUD_Menu->Destruct();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void AMenu_PC::HideMultiMenu()
{
	if (!HUD_MultiMenu) return;

	HUD_MultiMenu->RemoveFromParent();
	HUD_MultiMenu->Destruct();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}
