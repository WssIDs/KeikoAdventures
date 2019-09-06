// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "KALevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class KEIKOADVENTURES_API AKALevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	
	/** Begin play of current level. */
	virtual void BeginPlay() override;

	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

};

DECLARE_LOG_CATEGORY_EXTERN(LevelGameLog, Log, All);