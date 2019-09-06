// Fill out your copyright notice in the Description page of Project Settings.

#include "KAPlatformComponent.h"
#include "TimerManager.h"
#include <Components/ActorComponent.h>

DEFINE_LOG_CATEGORY(KAPlatformComponent);


UKAPlatformComponent::UKAPlatformComponent()
{
	TimeForRun = 1.0f;
}

void UKAPlatformComponent::DestroyAfterFalling()
{
	UE_LOG(KAPlatformComponent, Log, TEXT("Destroy Component"));
	DestroyComponent();

}

void UKAPlatformComponent::InitRagdollComponent()
{
	UE_LOG(KAPlatformComponent, Log, TEXT("Physics Start"));

	SetSimulatePhysics(true);

	GetWorld()->GetTimerManager().SetTimer(DestroyTimer,this, &UKAPlatformComponent::DestroyAfterFalling, 0.01f, false, 5.0f);
}

void UKAPlatformComponent::InitFall()
{
	UE_LOG(KAPlatformComponent, Log, TEXT("Init Fall Start"));
	GetWorld()->GetTimerManager().SetTimer(FallTimer, this, &UKAPlatformComponent::InitRagdollComponent, 0.01f, false, TimeForRun);
}

