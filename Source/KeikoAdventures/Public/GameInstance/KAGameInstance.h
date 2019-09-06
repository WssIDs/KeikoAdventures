// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KASaveGame.h"
#include "KAGame.h"
#include "KAGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class KEIKOADVENTURES_API UKAGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UKAGameInstance();

	UPROPERTY(BlueprintReadWrite)
	FString PlayerName;


	UPROPERTY(Category = CheckPoint, BlueprintReadWrite, SaveGame)
		FName LevelName;

	UPROPERTY(Category = CheckPoint, BlueprintReadWrite, SaveGame)
		FTransform LastCheckPoint;

	UPROPERTY(Category = Gameplay, BlueprintReadWrite, SaveGame)
	TMap<int32, FText> NewLastRecords;

	UPROPERTY(Category = Gameplay, BlueprintReadWrite, SaveGame)
	FTimespan FullGameTime;

	UPROPERTY(Category = Sounds, BlueprintReadWrite, SaveGame)
	float MasterSoundVolume = 1.0f;

	UPROPERTY(Category = Sounds, BlueprintReadWrite, SaveGame)
	float AmbientSoundVolume = 1.0f;

	UPROPERTY(Category = Sounds, BlueprintReadWrite, SaveGame)
	float MusicSoundVolume = 1.0f;

	UPROPERTY(Category = Sounds, BlueprintReadWrite, SaveGame)
	float VoiceSoundVolume = 1.0f;

	UPROPERTY(Category = Sounds, BlueprintReadWrite, SaveGame)
	float EffectSoundVolume = 1.0f;

	UPROPERTY(Category = Language, BlueprintReadWrite, SaveGame)
	FString Language;

	UPROPERTY(Category = Saving, BlueprintReadWrite)
	UKASaveGame* LoadSaveGameInstance;

	UFUNCTION(exec)
	void ClearRecords();

	/** virtual function to allow custom GameInstances an opportunity to set up what it needs */
	UFUNCTION()
	virtual void Init() override;

	/** virtual function to allow custom GameInstances an opportunity to do cleanup when shutting down */
	virtual void Shutdown() override;

private:
	
	UPROPERTY()
	AKAGame* Game;

public:

	UFUNCTION(BlueprintCallable, Category = Game)
		AKAGame* GetGame() { return Game; }

	UFUNCTION(BlueprintCallable, Category = Settings)
		void ResetAudioToDefaults();


	UFUNCTION(BlueprintCallable, Category = PuzlleGame)
		void SetGame(AKAGame* inGame)
	{
		Game = inGame;
	}
};

DECLARE_LOG_CATEGORY_EXTERN(SaveGameLog, Log, All);
