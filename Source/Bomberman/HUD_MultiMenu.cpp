// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_MultiMenu.h"

#include <Components/Button.h>
#include <Components/EditableTextBox.h>

void UHUD_MultiMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (HostButton) HostButton->OnClicked.AddDynamic(this, &UHUD_MultiMenu::OnHostClick);
	if (JoinButton) JoinButton->OnClicked.AddDynamic(this, &UHUD_MultiMenu::OnJoinClick);
}

void UHUD_MultiMenu::OnHostClick()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("HOST !!!"));
	/*
	AMenu_PC* PlayerController = Cast<AMenu_PC>(GetOwningPlayer());

	if (PlayerController != nullptr)
	{
		PlayerController->HideMenu();
	}

	UGameplayStatics::OpenLevel(this, FName("Game"));
	*/
}

void UHUD_MultiMenu::OnJoinClick()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("JOIN !!!"));
}