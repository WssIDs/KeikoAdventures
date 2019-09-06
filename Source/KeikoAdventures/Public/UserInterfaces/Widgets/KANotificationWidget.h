// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KAHUDWidget.h"
#include "KANotificationWidget.generated.h"

/**
 * 
 */
UCLASS()
class KEIKOADVENTURES_API UKANotificationWidget : public UKAHUDWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
		FText Value;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
		FLinearColor Color;
	
protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

};
