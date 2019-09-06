// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Engine.h"
#include "Animations/KAAnimInstance.h"
#include "KAKeikoAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class KEIKOADVENTURES_API UKAKeikoAnimInstance : public UKAAnimInstance
{
	GENERATED_BODY()
	
	
public:

	UPROPERTY(Category = Attack, EditDefaultsOnly, BlueprintReadWrite)
		float Pitch;

	UPROPERTY(Category = Attack, EditDefaultsOnly, BlueprintReadWrite)
		float Roll;

	UPROPERTY(Category = Attack, EditDefaultsOnly, BlueprintReadWrite)
		float Yaw;

	UPROPERTY(Category = Attack, EditDefaultsOnly, BlueprintReadWrite)
		bool bIsAttacking;

	UPROPERTY(Category = Attack, EditDefaultsOnly, BlueprintReadWrite)
		bool bIsFullBody;

	UPROPERTY(Category = Attack, EditDefaultsOnly, BlueprintReadWrite)
		bool bIsDied;

	UPROPERTY(Category = Attack, EditDefaultsOnly, BlueprintReadWrite)
		FRotator RotationLastTick;

	UPROPERTY(Category = Attack, EditDefaultsOnly, BlueprintReadWrite)
		float YawDelta;

public:



	// Executed when begin play is called on the owning component
	virtual void NativeBeginPlay() override;

	// the below functions are the native overrides for each phase
	// Native initialization override point
	virtual void NativeInitializeAnimation() override;

	// Native update override point. It is usually a good idea to simply gather data in this step and 
	// for the bulk of the work to be done in NativeUpdateAnimation.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	

	//These notifies are set in Montages to define end of attack and define when combo input will time out

	// Notify SaveAttack
	UFUNCTION()
		void AnimNotify_SaveAttack();

	// Notify ResetCombo
	UFUNCTION()
		void AnimNotify_ResetCombo();
};

DECLARE_LOG_CATEGORY_EXTERN(KAKeikoAnimInstanceLog, Log, All);

