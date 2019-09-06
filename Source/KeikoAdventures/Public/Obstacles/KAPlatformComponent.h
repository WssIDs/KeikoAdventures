// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "KAPlatformComponent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, ClassGroup = (Rendering, Common), editinlinenew, meta = (BlueprintSpawnableComponent))
class KEIKOADVENTURES_API UKAPlatformComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UKAPlatformComponent();

	UPROPERTY(Category = Test, EditAnywhere, BlueprintReadWrite)
		float TimeForRun;

	FTimerHandle FallTimer;
	FTimerHandle DestroyTimer;

	UFUNCTION()
		void DestroyAfterFalling();

	UFUNCTION()
		void InitRagdollComponent();

	UFUNCTION()
		void InitFall();
	
};


DECLARE_LOG_CATEGORY_EXTERN(KAPlatformComponent, Log, All);
