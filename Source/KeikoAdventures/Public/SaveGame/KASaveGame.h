// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "KASaveGame.generated.h"

/**
 * 
 */
UCLASS()
class KEIKOADVENTURES_API UKASaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	
	UPROPERTY(Category = GameInstance, BlueprintReadWrite, SaveGame)
	TArray<uint8> GameInstanceData;


	UPROPERTY(Category = GameInstance, BlueprintReadWrite, SaveGame)
	TArray<uint8> CharacterData;

	UPROPERTY(Category = GameInstance, BlueprintReadWrite, SaveGame)
	TArray<uint8> PlayerStateData;
};
