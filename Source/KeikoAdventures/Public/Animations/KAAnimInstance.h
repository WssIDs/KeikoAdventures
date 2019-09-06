// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "KAAnimInstance.generated.h"


class AKACharacter;

/**
 * 
 */
UCLASS()
class KEIKOADVENTURES_API UKAAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = FootIK, EditDefaultsOnly, BlueprintReadWrite)
		FVector HipOffset;
	
	UPROPERTY(Category = FootIK, EditDefaultsOnly, BlueprintReadWrite)
		FVector LeftFootEffectorLocation;

	UPROPERTY(Category = FootIK, EditDefaultsOnly, BlueprintReadWrite)
		FVector RightFootEffectorLocation;

	UPROPERTY(Category = FootIK, EditDefaultsOnly, BlueprintReadWrite)
		float RightAlpha;

	UPROPERTY(Category = FootIK, EditDefaultsOnly, BlueprintReadWrite)
		float LeftAlpha;

	UPROPERTY(Category = FootIK, EditDefaultsOnly, BlueprintReadWrite)
		float HipAlpha;


	UPROPERTY(Category = Locomotion, EditDefaultsOnly, BlueprintReadWrite)
		float Speed;

	UPROPERTY(Category = Locomotion, EditDefaultsOnly, BlueprintReadWrite)
		float Direction;

	UPROPERTY(Category = Locomotion, EditDefaultsOnly, BlueprintReadWrite)
		float VelocityZ;

	UPROPERTY(Category = Locomotion, EditDefaultsOnly, BlueprintReadWrite)
		bool bIsMoving;

	UPROPERTY(Category = Locomotion, EditDefaultsOnly, BlueprintReadWrite)
		bool bIsFalling;

	UPROPERTY(Category = Locomotion, EditDefaultsOnly, BlueprintReadWrite)
		bool bIsHardFalling;

	UPROPERTY(Category = Pawn, BlueprintReadOnly)
		AKACharacter* Character;

	// Executed when begin play is called on the owning component
	virtual void NativeBeginPlay() override;

	// the below functions are the native overrides for each phase
	// Native initialization override point
	virtual void NativeInitializeAnimation() override;

	// Native update override point. It is usually a good idea to simply gather data in this step and 
	// for the bulk of the work to be done in NativeUpdateAnimation.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(Category = Locomotion, BlueprintCallable)
		void CalculateMovement();

};
