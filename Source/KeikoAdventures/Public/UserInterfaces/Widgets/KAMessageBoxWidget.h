// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KAGameWidget.h"
#include "KAMessageBoxWidget.generated.h"

/**
 * 
 */
UCLASS()
class KEIKOADVENTURES_API UKAMessageBoxWidget : public UKAGameWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
		bool bPauseGame;

	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
		bool bShowMouseCursor;
	
	UPROPERTY(Category = Game, EditAnywhere, BlueprintReadWrite)
		FText TitleText;

	UPROPERTY(Category = Game, EditAnywhere, BlueprintReadWrite)
		FText SubTitleText;

	UPROPERTY(Category = Game, EditAnywhere, BlueprintReadWrite)
		FText FirstAdditionalText;

	UPROPERTY(Category = Game, EditAnywhere, BlueprintReadWrite)
		FText SecondAdditionalText;

	UPROPERTY(Category = Game, EditAnywhere, BlueprintReadWrite)
		FSlateColor TitleColor;
	

	virtual void NativeConstruct() override;
};
