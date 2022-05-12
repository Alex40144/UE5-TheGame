// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheGameGameMode.h"
#include "RTSController.h"
#include "RTSCamera.h"
#include "UObject/ConstructorHelpers.h"

ATheGameGameMode::ATheGameGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARTSController::StaticClass();
	
	DefaultPawnClass = ARTSCamera::StaticClass();
}