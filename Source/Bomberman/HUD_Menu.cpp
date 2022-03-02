// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_Menu.h"

#include "Menu_PC.h"
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

void UHUD_Menu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (B_Jouer != nullptr) B_Jouer->OnClicked.AddDynamic(this, &UHUD_Menu::OnJouerClick);
	if (B_Quitter != nullptr) B_Quitter->OnClicked.AddDynamic(this, &UHUD_Menu::OnQuitterClick);
}

void UHUD_Menu::OnJouerClick()
{
	AMenu_PC* PlayerController = Cast<AMenu_PC>(GetOwningPlayer());

	if (PlayerController != nullptr)
	{
		PlayerController->HideHUD_Menu();
	}

	UGameplayStatics::OpenLevel(this, FName("Game"));
}

void UHUD_Menu::OnQuitterClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}
