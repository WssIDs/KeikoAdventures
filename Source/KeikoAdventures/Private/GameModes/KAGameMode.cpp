// Fill out your copyright notice in the Description page of Project Settings.

#include "KAGameMode.h"
#include "KACharacter.h"
#include "KAHUD.h"
#include "KAPlayerState.h"
#include "KAPlayerController.h"


DEFINE_LOG_CATEGORY(GameModeLog);

AKAGameMode::AKAGameMode()
{
	HUDClass = AKAHUD::StaticClass();
	PlayerControllerClass = AKAPlayerController::StaticClass();
	DefaultPawnClass = AKACharacter::StaticClass();
	PlayerStateClass = AKAPlayerState::StaticClass();
}


