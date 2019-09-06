// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KAUserHUDWidget.h"
#include "KAGameMode.generated.h"

/**
 * 
 */
UCLASS()
class KEIKOADVENTURES_API AKAGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AKAGameMode();

	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UKAUserHUDWidget> WidgetClass;
	
	
};

DECLARE_LOG_CATEGORY_EXTERN(GameModeLog, Log, All);
