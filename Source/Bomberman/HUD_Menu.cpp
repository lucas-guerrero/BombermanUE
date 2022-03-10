// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_Menu.h"

#include "Menu_PC.h"
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

void UHUD_Menu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (SoloButton) SoloButton->OnClicked.AddDynamic(this, &UHUD_Menu::OnPlayClick);
	if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UHUD_Menu::OnQuitClick);
	if (MultiButton) MultiButton->OnClicked.AddDynamic(this, &UHUD_Menu::OnMultiClick);
}

void UHUD_Menu::OnPlayClick()
{
	AMenu_PC* PlayerController = Cast<AMenu_PC>(GetOwningPlayer());

	if (PlayerController != nullptr)
	{
		PlayerController->HideMenu();
	}

	UGameplayStatics::OpenLevel(this, FName("Game"));
}

void UHUD_Menu::OnMultiClick()
{
	
	AMenu_PC* PlayerController = Cast<AMenu_PC>(GetOwningPlayer());

	if (PlayerController != nullptr)
	{
		PlayerController->HideMenu();
		PlayerController->ShowMultiMenu();
	}
}

void UHUD_Menu::OnQuitClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}
