// Copyright Epic Games, Inc. All Rights Reserved.

#include "BatteryCollectorGameGameMode.h"
#include "BatteryCollectorGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABatteryCollectorGameGameMode::ABatteryCollectorGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
