// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KAWidget.generated.h"

class UKAGameInstance;

/**
 * 
 */
UCLASS()
class KEIKOADVENTURES_API UKAWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Category = Game, EditAnywhere, BlueprintReadWrite)
	UKAGameInstance* GameInstance;

protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
};
