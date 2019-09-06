// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Delegates/DelegateCombinations.h"
#include "KAUserHUDWidget.h"
#include <Sound/SoundCue.h>
#include "KAPlayerState.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(KAPlayerStateLog, Log, All);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FExpirienceGainedDelegate, int32, inExpirience);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLevelGainedDelegate, int32, inLevel);


/**
 * 
 */
UCLASS()
class KEIKOADVENTURES_API AKAPlayerState : public APlayerState
{
	GENERATED_BODY()


public:

	AKAPlayerState();

	virtual void BeginPlay() override;

	UPROPERTY(Category = "Level System", EditAnywhere, BlueprintReadWrite, SaveGame)
	int32 Level;

	UPROPERTY(Category = "Level System", EditAnywhere, BlueprintReadWrite, SaveGame)
	int32 Expirience;

	UPROPERTY(Category = "Level System", EditAnywhere, BlueprintReadWrite)
	int32 ExpirienceForLevelUp;

	int32 DefaultExpirience;

	UPROPERTY(Category = "Level System", BlueprintReadWrite)
		UKAUserHUDWidget* LevelUpWidget;

	UPROPERTY(Category = "Level System", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UCameraShake> LevelUpCameraShake;

	UPROPERTY(Category = "Level System", EditAnywhere, BlueprintReadWrite)
		USoundCue* LevelUpSound;

	UPROPERTY(Category = "Level System", EditAnywhere, BlueprintReadWrite)
		float LevelUpWidgetTimeLeft;

	/** Expirience gained Event */

	UPROPERTY(BlueprintAssignable, Category = "Level System", meta = (DisplayName = "OnExpirienceGainedEvent"))
		FExpirienceGainedDelegate ExpirienceGainedDelegate;
	
	UFUNCTION()
	virtual void ExpirienceGained(int32 inExpirience);

	UFUNCTION(BlueprintImplementableEvent)
		void OnExpirienceGained(int32 inExpirience);


	UPROPERTY(BlueprintAssignable, Category = "Level System", meta = (DisplayName = "OnLevelGainedEvent"))
		FLevelGainedDelegate LevelGainedDelegate;

	UFUNCTION()
	virtual void LevelGained(int32 inLevel);

	UFUNCTION(BlueprintImplementableEvent)
		void OnLevelGained(int32 inLevel);
	
	
	UFUNCTION(Category = "Level System", BlueprintCallable)
		void AddExpirience(int32 inExpirience);

	UFUNCTION(Category = "Level System", BlueprintCallable)
		void LevelUp(int32 inExprience);

	UFUNCTION(Category = "Level System", BlueprintCallable)
		void SetLevel(int32 inLevel);

	UFUNCTION(Category = "Level System", BlueprintCallable)
		void CalculateExpirienceForLevelUp();
	

private:

	UPROPERTY(Category = "Level System", EditAnywhere)
		TSubclassOf<UKAUserHUDWidget> LevelUpWidgetClass;

	FTimerHandle TimerLevelUpWidget;

	UFUNCTION()
		void HideLevelUpWidget();

};
