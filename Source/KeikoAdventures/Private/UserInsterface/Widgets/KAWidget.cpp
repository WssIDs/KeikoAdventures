// Fill out your copyright notice in the Description page of Project Settings.

#include "KAWidget.h"
#include "KAGameInstance.h"




void UKAWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (GetWorld()->GetGameInstance())
	{
		GameInstance = Cast<UKAGameInstance>(GetWorld()->GetGameInstance());
	}
}

void UKAWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
