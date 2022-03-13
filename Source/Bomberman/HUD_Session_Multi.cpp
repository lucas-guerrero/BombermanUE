// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_Session_Multi.h"

#include <Components/Button.h>

void UHUD_Session_Multi::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (LaunchButton) LaunchButton->OnClicked.AddDynamic(this, &UHUD_Session_Multi::OnLaunchClick);
	if (LeaveButton) LeaveButton->OnClicked.AddDynamic(this, &UHUD_Session_Multi::OnLeaveClick);
}

void UHUD_Session_Multi::OnLaunchClick()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("HOST !!!"));
}

void UHUD_Session_Multi::OnLeaveClick()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, EditTextIp->GetText().ToString());
}

void UHUD_Session_Multi::Autority()
{
	LeaveButton->SetIsEnabled(false);
}

void UHUD_Session_Multi::NotAutority()
{
	LaunchButton->SetIsEnabled(false);
}