// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "KAPlayerState.h"
#include "KAGameplayStatics.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class KEIKOADVENTURES_API UKAGameplayStatics : public UObject
{
	GENERATED_BODY()

public:

	/* Serialize object params to object data*/
	UFUNCTION(BlueprintCallable, Category = "GameplayStatics")
	static TArray<uint8> ObjectSaver(UObject * SaveObject);

	/* Deserialize object data to object params*/
	UFUNCTION(BlueprintCallable, Category = "GameplayStatics")
	static void ObjectLoader(UObject * LoadObject, TArray<uint8> ObjectData);

	/* Serialize object params to object data*/
	UFUNCTION(BlueprintCallable, Category = "GameplayStatics")
		static TArray<uint8> ActortSaver(AActor * SaveActor);

	/* Deserialize object data to object params*/
	UFUNCTION(BlueprintCallable, Category = "GameplayStatics")
		static void ActorLoader(AActor * LoadActor, TArray<uint8> ActorData);

	/* Change Localization at Runtime. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Change Localization"), Category = "Locale")
	static void ChangeLocalization(FString target);
};


DECLARE_LOG_CATEGORY_EXTERN(KAGameplayStaticsLog, Log, All)
