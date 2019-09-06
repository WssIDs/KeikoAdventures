// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KAWidget.h"
#include "KAGameWidget.generated.h"


class AKAGame;

/**
 * 
 */
UCLASS()
class KEIKOADVENTURES_API UKAGameWidget : public UKAWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Game, EditAnywhere, BlueprintReadWrite)
	AKAGame* Owner;

	UFUNCTION(BlueprintImplementableEvent)
	void OnChangedScore(int32 inScore);
	
protected:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;
	
};
