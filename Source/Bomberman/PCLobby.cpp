#include "PCLobby.h"
#include "HUD_Session_Multi.h"

void APCLobby::BeginPlay()
{
	Super::BeginPlay();

	ShowWaitMenu();
}

void APCLobby::ShowWaitMenu()
{
	if (!BP_HUD_SessionMenu) return;

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	HUD_SessionMenu = CreateWidget<UHUD_Session_Multi>(this, BP_HUD_SessionMenu);
	if (HUD_SessionMenu)
	{
		if (!HasAuthority()) HUD_SessionMenu->NotAutority();

		HUD_SessionMenu->AddToViewport();
	}
}

void APCLobby::HideWaitMenu()
{
	if (!HUD_SessionMenu) return;

	HUD_SessionMenu->RemoveFromParent();
	HUD_SessionMenu->Destruct();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void APCLobby::LaunchGame()
{
	HideWaitMenu();
	GetWorld()->ServerTravel(TEXT("Game"));
}