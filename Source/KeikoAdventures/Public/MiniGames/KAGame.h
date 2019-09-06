// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KAMessageBoxWidget.h"
#include "KANotificationWidget.h"
#include "Misc/Timespan.h"
#include "Delegates/DelegateCombinations.h"
#include "KAGame.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimeLeftDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameWinDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreChangedDelegate, int, inScore);


UCLASS(abstract)
class KEIKOADVENTURES_API AKAGame : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKAGame();

	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
	FLinearColor WinMessageColor;

	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
	FLinearColor LoseMessageColor;

	UPROPERTY(Category = Widget, BlueprintReadWrite)
	UKAGameWidget* GameInitWidget;

	UPROPERTY(Category = Widget, BlueprintReadWrite)
	UKAGameWidget* HUDWidget;

	UPROPERTY(Category = Widget, BlueprintReadWrite)
	UKAMessageBoxWidget* MessageBoxWidget;

	UPROPERTY(Category = Init, VisibleAnywhere, BlueprintReadWrite)
	bool bGameWin;

	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
	FTimespan CountDownTime;

	UPROPERTY(Category = Game, EditAnywhere, BlueprintReadWrite)
	int32 Score;

	UPROPERTY(Category = GameTime, BlueprintReadWrite)
	FTimespan CurrentTime;

	UPROPERTY(Category = GameTime, BlueprintReadWrite)
	FTimespan StartTime;

	UPROPERTY(Category = Init, VisibleAnywhere, BlueprintReadWrite)
	float DifficultCoefficient;

private:

	UPROPERTY(Category = Classes, EditAnywhere)
	TSubclassOf<UKAGameWidget> GameInitWidgetClass;

	UPROPERTY(Category = Classes, EditAnywhere)
	TSubclassOf<UKAGameWidget> HUDWidgetClass;

	UPROPERTY(Category = Classes, EditAnywhere)
	TSubclassOf<UKAMessageBoxWidget> MessageBoxWidgetClass;

	UPROPERTY(Category = Classes, EditAnywhere)
	TSubclassOf<UKANotificationWidget> ChangeScoreWidgetClass;

	UPROPERTY(Category = Classes, EditAnywhere)
	TSubclassOf<UKANotificationWidget> ChangeTimeWidgetClass;

	FTimerHandle GameManager;
	FTimerHandle TimeManager;

	// Метод вызываемый таймером каждую секунду
	void CalculateTime();
	// Метод вызывваемый таймером каждый тик
	void CalculateGame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Show Message for Lose or Win
	UFUNCTION(Category = Init, BlueprintCallable)
	virtual void ShowMessage(FText TitleText, FText SubTitleText, FLinearColor Color);

	virtual void ShowMessage(FText TitleText, FText SubTitleText, FText FirstAdditionalText, FLinearColor Color);

	virtual void ShowMessage(FText TitleText, FText SubTitleText, FText FirstAdditionalText, FText SecondAdditionalText, FLinearColor Color);

	UFUNCTION(Category = GamePlay, BlueprintCallable)
	virtual void AddTime(float inTime);

	UFUNCTION(Category = GamePlay, BlueprintCallable)
	virtual void RemoveTime(float inTime);

	UFUNCTION(Category = GamePlay, BlueprintCallable)
	virtual void AddScore(int32 inScore);

	UFUNCTION(Category = GamePlay, BlueprintCallable)
	virtual void RemoveScore(int32 inScore);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Category = Gameplay, BlueprintCallable)
	virtual void Init();

	// Replay game
	UFUNCTION(Category = Gameplay, BlueprintCallable)
	virtual void Replay();

	// Start game
	UFUNCTION(Category = Gameplay, BlueprintCallable)
		virtual void Start();

	UFUNCTION(Category = Gameplay, BlueprintCallable)
		virtual void TogglePause();

	// Stop game
	UFUNCTION(Category = Gameplay, BlueprintCallable)
		virtual void Stop();


	UPROPERTY(BlueprintAssignable, Category = "Game", meta = (DisplayName = "OnTimeLeftEvent"))
		FTimeLeftDelegate TimeLeftDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Game", meta = (DisplayName = "OnGameWinEvent"))
		FGameWinDelegate GameWinDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Game", meta = (DisplayName = "OnScoreChangedEvent"))
		FScoreChangedDelegate ScoreChangedDelegate;

	UFUNCTION()
	virtual  void TimeLeft();

	UFUNCTION(BlueprintImplementableEvent)
		void OnTimeLeft();

	UFUNCTION()
	virtual void GameWin();

	UFUNCTION(BlueprintImplementableEvent)
		void OnGameWin();
	
	UFUNCTION()
	virtual void ScoreChanged(int32 inScore);

	UFUNCTION(BlueprintImplementableEvent)
		void OnScoreChanged(int32 inScore);

#if WITH_EDITOR

	virtual void OnConstruction(const FTransform& Transform) override;

#endif

};

DECLARE_LOG_CATEGORY_EXTERN(GameLog, Log, All);