// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KAHUD.generated.h"

class UKAHUDWidget;
class UKAUserHUDWidget;

/**
 * 
 */
UCLASS()
class KEIKOADVENTURES_API AKAHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	AKAHUD();

	UPROPERTY(Category = UI, BlueprintReadWrite)
		UKAUserHUDWidget* UserWidget;

	UPROPERTY(Category = UI, BlueprintReadWrite)
		UKAHUDWidget* PauseMenuWidget;

	UFUNCTION(BlueprintCallable)
		void ShowPauseMenu();

	UFUNCTION(BlueprintCallable)
		void ClosePauseMenu();

	UFUNCTION(BlueprintCallable)
		void EnablePauseMenu(bool bShowPauseMenu);

private:

	UPROPERTY(Category = Classes, EditAnywhere)
	TSubclassOf<UKAHUDWidget> PauseMenuWidgetClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
