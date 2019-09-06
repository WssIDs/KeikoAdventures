// Fill out your copyright notice in the Description page of Project Settings.

#include "KALevelTeleportActor.h"
#include <FileManager.h>
#include <Paths.h>
#include <Kismet/GameplayStatics.h>
#include <Engine/LevelStreaming.h>
#include <UserWidget.h>

void AKALevelTeleportActor::Interact()
{
	Super::Interact();

	TArray<FString> MapFiles;

	IFileManager::Get().FindFilesRecursive(MapFiles, *FPaths::GameContentDir(), TEXT(".umap"), true, false);

	FString FindName = NextLevel.ToString();

	if (!LoadingScreenWidget)
	{
		LoadingScreenWidget = CreateWidget<UUserWidget>(GetWorld(), LoadingScreenClass);
	}

	if (!(LoadingScreenWidget->IsInViewport()))
	{
		LoadingScreenWidget->AddToViewport(10);
	}

	if (MapFiles.Find(FindName.Append(TEXT(".umap"))) >= 0)
	{
		FLatentActionInfo LatentInfo;
		ULevelStreaming* LevelStreaming = UGameplayStatics::GetStreamingLevel(GetWorld(), NextLevel);
		LevelStreaming->OnLevelLoaded.AddDynamic(this, &AKALevelTeleportActor::LoadNextLevel);
		UGameplayStatics::LoadStreamLevel(GetWorld(), NextLevel, false, false, LatentInfo);
		UGameplayStatics::UnloadStreamLevel(GetWorld(), *UGameplayStatics::GetCurrentLevelName(GetWorld()), LatentInfo, false);
	}
	else
	{
		FLatentActionInfo LatentInfo;
		ULevelStreaming* LevelStreaming = UGameplayStatics::GetStreamingLevel(GetWorld(), TEXT("Transition"));
		LevelStreaming->OnLevelLoaded.AddDynamic(this, &AKALevelTeleportActor::LoadMainLevel);
		UGameplayStatics::LoadStreamLevel(GetWorld(), TEXT("Transition"), false, false, LatentInfo);
		UGameplayStatics::UnloadStreamLevel(GetWorld(),*UGameplayStatics::GetCurrentLevelName(GetWorld()),LatentInfo,false);
	}
}

void AKALevelTeleportActor::LoadNextLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), NextLevel, false);
}

void AKALevelTeleportActor::LoadMainLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Transition"), false);
}
