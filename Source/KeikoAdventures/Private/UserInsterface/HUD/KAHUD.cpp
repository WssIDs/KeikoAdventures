// Fill out your copyright notice in the Description page of Project Settings.

#include "KAHUD.h"
#include "Kismet/GameplayStatics.h"
#include "KAGameMode.h"


AKAHUD::AKAHUD()
{

}

void AKAHUD::ShowPauseMenu()
{
	if (!PauseMenuWidget)
	{
		PauseMenuWidget = CreateWidget<UKAHUDWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), PauseMenuWidgetClass);
	}

	PauseMenuWidget->AddToViewport(0);

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PC)
	{
		PC->bShowMouseCursor = true;
		const FInputModeGameAndUI InputMode = FInputModeGameAndUI();
		PC->SetInputMode(InputMode);
		
		UGameplayStatics::SetGamePaused(GetWorld(),true);
	}
}

void AKAHUD::ClosePauseMenu()
{
	if (PauseMenuWidget)
	{
		PauseMenuWidget->RemoveFromParent();
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PC)
	{
		PC->bShowMouseCursor = false;
		const FInputModeGameOnly InputMode = FInputModeGameOnly();
		PC->SetInputMode(InputMode);

		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
}

void AKAHUD::EnablePauseMenu(bool bShowPauseMenu)
{
	if (bShowPauseMenu)
	{
		ShowPauseMenu();
	}
	else
	{
		ClosePauseMenu();
	}
}

void AKAHUD::BeginPlay()
{
	AKAGameMode* GameMode = Cast<AKAGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GameMode)
	{
		if (!UserWidget)
		{
			UserWidget = CreateWidget<UKAUserHUDWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), GameMode->WidgetClass);
		}

		UserWidget->AddToViewport(0);
	}

}
