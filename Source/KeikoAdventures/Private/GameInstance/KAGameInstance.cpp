// Fill out your copyright notice in the Description page of Project Settings.

#include "KAGameInstance.h"
#include "KACharacter.h"

#include "Kismet/GameplayStatics.h"
#include "KAGameplayStatics.h"
#include "KAPlayerController.h"

DEFINE_LOG_CATEGORY(SaveGameLog);

UKAGameInstance::UKAGameInstance()
{
	Language = TEXT("ru");

	LastCheckPoint.SetLocation(FVector(950.0f, 290.0f, 218.0f));
	LastCheckPoint.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
}

void UKAGameInstance::ClearRecords()
{
	if (NewLastRecords.Num() > 0)
	{
		NewLastRecords.Empty();
	}
}

void UKAGameInstance::Init()
{
	Super::Init();

	if (LoadSaveGameInstance == nullptr)
	{
		if (UGameplayStatics::DoesSaveGameExist(TEXT("Saves"), 0))
		{

			LoadSaveGameInstance = Cast<UKASaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Saves"), 0));


			if (LoadSaveGameInstance)
			{
				UE_LOG(SaveGameLog, Warning, TEXT("LoadSaveGameInstance Loaded"));

				UKAGameplayStatics::ObjectLoader(this, LoadSaveGameInstance->GameInstanceData);
				UKAGameplayStatics::ChangeLocalization(Language);

				UE_LOG(SaveGameLog, Warning, TEXT("GI Init"));
				
			}
		}
		else
		{
			UE_LOG(SaveGameLog, Error, TEXT("LoadSaveGameInstance not exist"));
			
			if (!LoadSaveGameInstance)
			{
				LoadSaveGameInstance = Cast<UKASaveGame>(UGameplayStatics::CreateSaveGameObject(UKASaveGame::StaticClass()));
				UE_LOG(SaveGameLog,Warning, TEXT("LoadSaveGameInstance has been created"));
			}
		}
	}
	else
	{
		UE_LOG(SaveGameLog,Warning, TEXT("LoadSaveGameInstance has been loaded"));
	}
}

void UKAGameInstance::Shutdown()
{
	FullGameTime += FTimespan::FromSeconds(GetWorld()->TimeSeconds);

	if (!LoadSaveGameInstance)
	{
		LoadSaveGameInstance = Cast<UKASaveGame>(UGameplayStatics::CreateSaveGameObject(UKASaveGame::StaticClass()));
		UE_LOG(SaveGameLog,Warning, TEXT("LoadSaveGameInstance has been created"));
	}

	LoadSaveGameInstance->GameInstanceData = UKAGameplayStatics::ObjectSaver(this);
	
	UGameplayStatics::SaveGameToSlot(LoadSaveGameInstance, TEXT("Saves"), 0);

	UE_LOG(SaveGameLog, Warning, TEXT("GameInstance Shudown"));	
	Super::Shutdown();
}

void UKAGameInstance::ResetAudioToDefaults()
{
	MasterSoundVolume = 1.0f;
	AmbientSoundVolume = 1.0f;
	MusicSoundVolume = 1.0f;
	VoiceSoundVolume = 1.0f;
	EffectSoundVolume = 1.0f;
}