#include "HUDFinish.h"

#include <string>
#include <Components/TextBlock.h>

void UHUDFinish::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UHUDFinish::SetResultat(FText Text)
{
	if (Resultat) Resultat->SetText(Text);
}

void UHUDFinish::SetCompteur(float Time)
{
	int Seconde = Time;
	FString String = FString::Printf(TEXT("Return To Menu: %d"), Seconde);

	if (Compteur) Compteur->SetText(FText::AsCultureInvariant(String));
}
