// Fill out your copyright notice in the Description page of Project Settings.

#include "KAPlayerState.h"
#include <Kismet/GameplayStatics.h>
#include "KACharacter.h"


DEFINE_LOG_CATEGORY(KAPlayerStateLog);

AKAPlayerState::AKAPlayerState()
{
	DefaultExpirience = 100;
	ExpirienceForLevelUp = 100;
	Level = 1;

	LevelUpWidgetTimeLeft = 3.0f;

	// Binding Delegates
	ExpirienceGainedDelegate.AddDynamic(this, &AKAPlayerState::ExpirienceGained);
	LevelGainedDelegate.AddDynamic(this, &AKAPlayerState::LevelGained);
}

void AKAPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void AKAPlayerState::ExpirienceGained(int32 inExpirience)
{
	// Вызов только в Blueprint
	OnExpirienceGained(inExpirience);

	UE_LOG(KAPlayerStateLog,Log,TEXT("Expirience gained = %d"),inExpirience)
}

void AKAPlayerState::LevelGained(int32 inLevel)
{
	// Вызов только в Blueprint
	OnLevelGained(inLevel);

	if (!LevelUpWidget)
	{
		LevelUpWidget = CreateWidget<UKAUserHUDWidget>(GetWorld(), LevelUpWidgetClass);
	}

	if (!(LevelUpWidget->IsInViewport()))
	{
		LevelUpWidget->AddToViewport(-1);
	}

	if (GetWorldTimerManager().IsTimerActive(TimerLevelUpWidget))
	{
		GetWorldTimerManager().ClearTimer(TimerLevelUpWidget);
	}

	GetWorldTimerManager().SetTimer(TimerLevelUpWidget, this, &AKAPlayerState::HideLevelUpWidget,GetWorld()->GetDeltaSeconds(), false, LevelUpWidgetTimeLeft );

	UE_LOG(KAPlayerStateLog, Log, TEXT("Level gained = %d"), inLevel);
}

void AKAPlayerState::AddExpirience(int32 inExpirience)
{
	Expirience += inExpirience;

	ExpirienceGainedDelegate.Broadcast(inExpirience);

	while (Expirience >= ExpirienceForLevelUp)
	{
		LevelUp(Expirience - ExpirienceForLevelUp);
	}
}

void AKAPlayerState::LevelUp(int32 inExpirience)
{
	Expirience = inExpirience;
	Level++;
	
	if (inExpirience < ExpirienceForLevelUp)
	{
		LevelGainedDelegate.Broadcast(Level);
	}

	CalculateExpirienceForLevelUp();

	AKACharacter* KACharacter = Cast<AKACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (KACharacter)
	{
		KACharacter->CalculateCharacterStats();
	}
}

void AKAPlayerState::SetLevel(int32 inLevel)
{

}

void AKAPlayerState::CalculateExpirienceForLevelUp()
{
	ExpirienceForLevelUp = Level * DefaultExpirience;
}

void AKAPlayerState::HideLevelUpWidget()
{
	if (LevelUpWidget)
	{
		if (LevelUpWidget->IsInViewport())
		{
			LevelUpWidget->RemoveFromParent();
		}
	}

	GetWorldTimerManager().ClearTimer(TimerLevelUpWidget);
}
