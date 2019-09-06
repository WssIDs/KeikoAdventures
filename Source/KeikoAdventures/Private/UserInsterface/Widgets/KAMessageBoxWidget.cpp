// Fill out your copyright notice in the Description page of Project Settings.

#include "KAMessageBoxWidget.h"
#include "Kismet/GameplayStatics.h"



void UKAMessageBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (bShowMouseCursor)
	{
		PC->SetInputMode(FInputModeUIOnly());
		PC->bShowMouseCursor = true;
	}

	if (bPauseGame)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}
