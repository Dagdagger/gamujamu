// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameuJamuGameMode.h"
#include "GameuJamuPlayerController.h"
#include "GameuJamuCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGameuJamuGameMode::AGameuJamuGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGameuJamuPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}