// Fill out your copyright notice in the Description page of Project Settings.

#include "KALevelScriptActor.h"
#include "KAGameInstance.h"
#include "KAPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "KAPlayerState.h"
#include "KAGameplayStatics.h"
#include "KACharacter.h"
#include <GameFramework/Controller.h>

DEFINE_LOG_CATEGORY(LevelGameLog);

void AKALevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LevelGameLog, Log, TEXT("Level is Alive"));

	UKAGameInstance* GameInstance = Cast<UKAGameInstance>(GetGameInstance());
	
	if (GameInstance)
	{
		UE_LOG(LevelGameLog, Log, TEXT("GameInstance is Alive"));

		APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		if (Controller)
		{
			UE_LOG(LevelGameLog, Log, TEXT("Controller is Alive"));

			APlayerState* PState = Controller->PlayerState;

			if (PState)
			{

				UE_LOG(LevelGameLog, Log, TEXT("PayerState is Alive"));

				PState->SetPlayerName(GameInstance->PlayerName);

				UE_LOG(LevelGameLog, Log, TEXT("Player Name - %s"),*PState->GetPlayerName());
			}
		}
	}
}

void AKALevelScriptActor::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
