#include "HUD_Session_Multi.h"

#include <Components/Button.h>

void UHUD_Session_Multi::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UHUD_Session_Multi::NotAutority()
{
	if (LaunchButton) LaunchButton->SetIsEnabled(false);
}