// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestructibleActor.h"
#include "Interfaces/InteractedInterface.h"
#include "KADestructibleActor.generated.h"

/**
 * 
 */
UCLASS()
class KEIKOADVENTURES_API AKADestructibleActor : public ADestructibleActor, public IItemInterface
{
	GENERATED_BODY()
	
public:
	AKADestructibleActor();
	
	UPROPERTY(Category = "Score", BlueprintReadWrite, EditAnywhere)
		int32 Score;

	UPROPERTY(Category = "Score", BlueprintReadWrite, EditAnywhere)
		int32 Expirience;

	UPROPERTY()
		bool bIsBonusAdded;

	UFUNCTION(BlueprintCallable)
	virtual void ChangeScore() override;

	UFUNCTION()
	void OnFracture(const FVector& HitPoint,const FVector& HitDirection);
};
