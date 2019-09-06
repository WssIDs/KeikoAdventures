// Fill out your copyright notice in the Description page of Project Settings.

#include "KADestructibleActor.h"
#include "DestructibleComponent.h"
#include "KAPlayerState.h"
#include "Kismet/GameplayStatics.h"

AKADestructibleActor::AKADestructibleActor()
{
	GetDestructibleComponent()->BodyInstance.SetUseAsyncScene(false);

	Score = 10;
	Expirience = 10;
	
	OnActorFracture.AddDynamic(this, &AKADestructibleActor::OnFracture);
}

void AKADestructibleActor::ChangeScore()
{
	if (!bIsBonusAdded)
	{
		AKAPlayerState* PState = Cast<AKAPlayerState>((UGameplayStatics::GetPlayerController(GetWorld(), 0))->PlayerState);
		PState->Score += Score;
		PState->AddExpirience(Expirience);
		bIsBonusAdded = true;
	}
}

void AKADestructibleActor::OnFracture(const FVector& HitPoint, const FVector& HitDirection)
{
	ChangeScore();
}
