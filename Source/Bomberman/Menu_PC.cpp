// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu_PC.h"
#include "HUD_Menu.h"
#include "HUD_MultiMenu.h"
#include "HUD_Session_Multi.h"

#include <Kismet/GameplayStatics.h>

void AMenu_PC::BeginPlay()
{
	Super::BeginPlay();

	FString levelName = GetWorld()->GetMapName();

	if (levelName.Contains(FString("MainMenu"))) ShowMenu();

	if (levelName.Contains(FString("SessionMap")))
	{
		ShowWaitMenu();
		if (HasAuthority()) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Serveur"));
		else GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Client"));
	}
}

void AMenu_PC::ShowMenu()
{
	if (!BP_HUD_Menu) return;

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	HUD_Menu = CreateWidget<UHUD_Menu>(this, BP_HUD_Menu);
	if (HUD_Menu) HUD_Menu->AddToViewport();
}

void AMenu_PC::ShowMultiMenu()
{
	if (!BP_HUD_MultiMenu) return;

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	HUD_MultiMenu = CreateWidget<UHUD_MultiMenu>(this, BP_HUD_MultiMenu);
	if (HUD_MultiMenu) HUD_MultiMenu->AddToViewport();
}

void AMenu_PC::ShowWaitMenu()
{
	if (!BP_HUD_SessionMenu) return;

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	HUD_SessionMenu = CreateWidget<UHUD_Session_Multi>(this, BP_HUD_SessionMenu);
	if (HUD_SessionMenu)
	{
		if(HasAuthority()) HUD_SessionMenu->Autority();
		else HUD_SessionMenu->NotAutority();

		HUD_SessionMenu->AddToViewport();
	}
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

void AMenu_PC::HideWaitMenu()
{
	if (!HUD_SessionMenu) return;

	HUD_SessionMenu->RemoveFromParent();
	HUD_SessionMenu->Destruct();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void AMenu_PC::LaunchGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Travel !!!"));
	GetWorld()->ServerTravel(TEXT("Game"));
}
