// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDFinish.h"

#include <string>
#include <Components/TextBlock.h>

void UHUDFinish::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UHUDFinish::SetResultat(FText Text)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Change Text"));
	if (Resultat) Resultat->SetText(Text);
}

void UHUDFinish::SetCompteur(float Time)
{
	int Seconde = Time;
	FString String = FString::Printf(TEXT("Return To Menu: %d"), Seconde);

	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, String);

	if (Compteur) Compteur->SetText(FText::AsCultureInvariant(String));
}
