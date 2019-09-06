// Fill out your copyright notice in the Description page of Project Settings.

#include "KAGame.h"
#include "Kismet/GameplayStatics.h"
#include "KAPlayerState.h"
#include "KAHUD.h"
#include "KAUserHUDWidget.h"
#include "TimerManager.h"
#include "KAGameInstance.h"
#include "KAPlayerController.h"

DEFINE_LOG_CATEGORY(GameLog);


#define LOCTEXT_NAMESPACE "GAME"

// Sets default values
AKAGame::AKAGame()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TimeLeftDelegate.AddDynamic(this, &AKAGame::TimeLeft);
	GameWinDelegate.AddDynamic(this, &AKAGame::GameWin);

	ScoreChangedDelegate.AddDynamic(this, &AKAGame::ScoreChanged);
}

void AKAGame::CalculateTime()
{
	if (!CurrentTime.IsZero())
	{
		if (!bGameWin)
		{
			CurrentTime -= FTimespan::FromSeconds(1.0f);
		}
	}
}

void AKAGame::CalculateGame()
{
	if (!CurrentTime.IsZero())
	{
		if (bGameWin)
		{
			GameWinDelegate.Broadcast();
		}
	}
	else
	{
		TimeLeftDelegate.Broadcast();
	}
}

// Called when the game starts or when spawned
void AKAGame::BeginPlay()
{
	Super::BeginPlay();
}

void AKAGame::Init()
{
	// GameInstance
	UKAGameInstance* GI = Cast<UKAGameInstance>(GetGameInstance());
	if (GI) // Проверка существования GameInstance
	{
		UE_LOG(GameLog, Log, TEXT("GameInstance %s"), *GI->GetName());
		
		// Назначаем в GameInstance текущую мини игру
		GI->SetGame(this);

		if(!GameInitWidget)
		{
			GameInitWidget = CreateWidget<UKAGameWidget>(GetWorld(), GameInitWidgetClass);

			GameInitWidget->Owner = this;
			UGameplayStatics::SetGamePaused(GetWorld(),false);
		}
		
		if (!(GameInitWidget->IsInViewport()))
		{
			GameInitWidget->AddToViewport(10);
		}

		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC)
		{
			UE_LOG(GameLog, Log, TEXT("PlayerController %s"), *PC->GetName());

			PC->bShowMouseCursor = true;
			const FInputModeUIOnly InputMode = FInputModeUIOnly();
			PC->SetInputMode(InputMode);
		}
	}
}

void AKAGame::Start()
{
	if (!HUDWidget)
	{
		HUDWidget = CreateWidget<UKAGameWidget>(GetWorld(), HUDWidgetClass);
		HUDWidget->Owner = this;

		ScoreChangedDelegate.AddDynamic(HUDWidget, &UKAGameWidget::OnChangedScore);
	}

	if (!(HUDWidget->IsInViewport()))
	{
		HUDWidget->AddToViewport(0);
	}


	GetWorldTimerManager().SetTimer(TimeManager, this, &AKAGame::CalculateTime, 1.0f, true);
	GetWorldTimerManager().SetTimer(GameManager, this, &AKAGame::CalculateGame, GetWorld()->GetDeltaSeconds(), true);
}

void AKAGame::TogglePause()
{
	if (!GetWorldTimerManager().IsTimerPaused(TimeManager) && !GetWorldTimerManager().IsTimerPaused(GameManager))
	{
		GetWorldTimerManager().PauseTimer(TimeManager);
		GetWorldTimerManager().PauseTimer(GameManager);
	}
	else
	{
		GetWorldTimerManager().UnPauseTimer(TimeManager);
		GetWorldTimerManager().UnPauseTimer(GameManager);
	}
}

void AKAGame::Replay()
{
}

void AKAGame::Stop()
{
	GetWorldTimerManager().ClearTimer(TimeManager);
	GetWorldTimerManager().ClearTimer(GameManager);
}

void AKAGame::ShowMessage(FText TitleText, FText SubTitleText, FLinearColor Color)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!MessageBoxWidget)
	{
		MessageBoxWidget = CreateWidget<UKAMessageBoxWidget>(PC, MessageBoxWidgetClass);
	}

	MessageBoxWidget->Owner = this;
	MessageBoxWidget->TitleText = TitleText;
	MessageBoxWidget->SubTitleText = SubTitleText;
	MessageBoxWidget->TitleColor = Color;
	MessageBoxWidget->FirstAdditionalText = FText::FromString("");
	MessageBoxWidget->SecondAdditionalText = FText::FromString("");

	MessageBoxWidget->AddToViewport(0);
}

void AKAGame::ShowMessage(FText TitleText, FText SubTitleText, FText FirstAdditionalText, FLinearColor Color)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!MessageBoxWidget)
	{
		MessageBoxWidget = CreateWidget<UKAMessageBoxWidget>(PC, MessageBoxWidgetClass);
	}

	MessageBoxWidget->Owner = this;
	MessageBoxWidget->TitleText = TitleText;
	MessageBoxWidget->SubTitleText = SubTitleText;
	MessageBoxWidget->TitleColor = Color;
	MessageBoxWidget->FirstAdditionalText = FirstAdditionalText;
	MessageBoxWidget->SecondAdditionalText = FText::FromString("");

	MessageBoxWidget->AddToViewport(0);
}

void AKAGame::ShowMessage(FText TitleText, FText SubTitleText, FText FirstAdditionalText, FText SecondAdditionalText, FLinearColor Color)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!MessageBoxWidget)
	{
		MessageBoxWidget = CreateWidget<UKAMessageBoxWidget>(PC, MessageBoxWidgetClass);
	}

	MessageBoxWidget->Owner = this;
	MessageBoxWidget->TitleText = TitleText;
	MessageBoxWidget->SubTitleText = SubTitleText;
	MessageBoxWidget->TitleColor = Color;
	MessageBoxWidget->FirstAdditionalText = FirstAdditionalText;
	MessageBoxWidget->SecondAdditionalText = SecondAdditionalText;

	MessageBoxWidget->AddToViewport(0);
}

void AKAGame::AddTime(float inTime)
{
	CurrentTime += FTimespan::FromSeconds(inTime);
}

void AKAGame::RemoveTime(float inTime)
{
	if (CurrentTime > FTimespan::FromSeconds(inTime + 1))
	{
		CurrentTime -= FTimespan::FromSeconds(inTime);
	}
}

void AKAGame::AddScore(int32 inScore)
{
	ScoreChangedDelegate.Broadcast(inScore);
	Score += inScore;
}

void AKAGame::RemoveScore(int32 inScore)
{
	if (Score >= inScore)
	{
		Score -= inScore;
		ScoreChangedDelegate.Broadcast(inScore*-1);
	}
	else
	{
		Score = 0;
	}
}

// Called every frame
void AKAGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKAGame::TimeLeft()
{
	UE_LOG(GameLog, Error, TEXT("TimeLeft"));

	HUDWidget->RemoveFromParent();

	OnTimeLeft();

	Stop();

	FText LoseMessage = LOCTEXT("LoseMessage", "YOU LOSE!");
	FText LoseSubMessage = LOCTEXT("LoseSubMessage", "Times is Over");

	ShowMessage(LoseMessage, LoseSubMessage, LoseMessageColor);
}

void AKAGame::GameWin()
{
	UE_LOG(GameLog, Log, TEXT("Game Win"));

	HUDWidget->RemoveFromParent();

	OnGameWin();

	Stop();

	UKAGameInstance* GameInstance = Cast<UKAGameInstance>(GetGameInstance());

	if (GameInstance)
	{
		FTimespan NewTime = StartTime - CurrentTime;

		// Add score after game 
		int32 AdditionalScore = FMath::RoundToInt(NewTime.GetTotalSeconds()) * DifficultCoefficient;

		AddScore(AdditionalScore);

		AKAPlayerState* PState = Cast<AKAPlayerState>((UGameplayStatics::GetPlayerController(GetWorld(), 0))->PlayerState);

		PState->Score += Score;

		// Need for SaveGame
		// Begin
		bool bContainsScore = GameInstance->NewLastRecords.Contains(PState->Score);

		if (!bContainsScore)
		{
			UE_LOG(GameLog, Error, TEXT("Current Record null"));
			GameInstance->NewLastRecords.Add(PState->Score, FText::FromString(PState->GetPlayerName()));
		}

		else
		{
			FText* Name = GameInstance->NewLastRecords.Find(PState->Score);
			UE_LOG(GameLog, Error, TEXT("Current Record = %s"), Name);

			GameInstance->NewLastRecords.Emplace(PState->Score, FText::FromString(PState->GetPlayerName()));
		}

		if (GameInstance->NewLastRecords.Num() > 0)
		{
			GameInstance->NewLastRecords.KeySort([](int32 A, int32 B) {return A > B; });
			UE_LOG(GameLog, Log, TEXT("Record Sorted"));
		}
		// End

		FText WinMessage = LOCTEXT("WinMessage", "TASK COMPLETE!");

		FFormatNamedArguments Arguments;
		Arguments.Add(TEXT("WinsScore"), Score);
		FText WinSubMessage = FText::Format(LOCTEXT("WinSubMessage", "Score: {WinsScore}"), Arguments);

		FFormatNamedArguments AdditionalArguments;
		AdditionalArguments.Add(TEXT("AdditionalScore"), AdditionalScore);
		FText WinAdditionalMessage = FText::Format(LOCTEXT("WinFirstAdditionalMessage", "Score for time: {AdditionalScore}"), AdditionalArguments);

		int OverallScore = Score + AdditionalScore;

		FFormatNamedArguments OverallArguments;
		OverallArguments.Add(TEXT("OverallScore"), OverallScore);
		FText WinTotalMessage = FText::Format(LOCTEXT("WinSecondAdditionalMessage", "Total: {OverallScore}"), OverallArguments);

		ShowMessage(WinMessage, WinSubMessage, WinAdditionalMessage, WinTotalMessage, WinMessageColor);
	}
}

void AKAGame::ScoreChanged(int32 inScore)
{
	OnScoreChanged(inScore);

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	UKANotificationWidget* ChangeScoreWidget = CreateWidget<UKANotificationWidget>(PC, ChangeScoreWidgetClass);

	if (ChangeScoreWidget)
	{
		if (inScore < 0)
		{
			ChangeScoreWidget->Value = FText::FromString(FString::FromInt(inScore));
			ChangeScoreWidget->Color = FLinearColor::Red;

		}
		else if (inScore > 0)
		{
			ChangeScoreWidget->Value = FText::FromString("+" + FString::FromInt(inScore));
			ChangeScoreWidget->Color = FLinearColor::Green;
		}			
		
		ChangeScoreWidget->AddToViewport(0);
	}
}

#if WITH_EDITOR

void AKAGame::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
}

#endif

#undef LOCTEXT_NAMESPACE