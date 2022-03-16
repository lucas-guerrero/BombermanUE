#include "PCGame.h"
#include "HUDFinish.h"

void APCGame::BeginPlay()
{
	Super::BeginPlay();
}

void APCGame::ShowFinish(bool IsWinner)
{
	if (!BP_HUDFinish) return;

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	HUD_Finish = CreateWidget<UHUDFinish>(this, BP_HUDFinish);
	if (HUD_Finish)
	{
		if (IsWinner) HUD_Finish->SetResultat(FText::FromString(TEXT("Winner")));
		HUD_Finish->AddToViewport();
	}
}

void APCGame::Finish(bool IsWinner)
{
	if (HUD_Finish) return;
	ShowFinish(IsWinner);
}
