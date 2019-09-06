// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "KAHUDWidget.h"
#include "KAUserHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class KEIKOADVENTURES_API UKAUserHUDWidget : public UKAHUDWidget
{
	GENERATED_BODY()	
	
public:

	UFUNCTION(BlueprintImplementableEvent)
		void OnChangedScore(int32 inScore);
};
