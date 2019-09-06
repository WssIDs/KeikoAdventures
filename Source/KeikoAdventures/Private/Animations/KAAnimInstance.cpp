// Fill out your copyright notice in the Description page of Project Settings.

#include "KAAnimInstance.h"
#include "KACharacter.h"

void UKAAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UKAAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<AKACharacter>(TryGetPawnOwner());
}

void UKAAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	CalculateMovement();
}

void UKAAnimInstance::CalculateMovement()
{
	if(Character)
	{ 
		Direction = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
		Speed = Character->GetVelocity().Size();
		bIsFalling = Character->GetCharacterMovement()->IsFalling();
		bIsMoving = Character->bMoving;

		if (bIsFalling)
		{
			VelocityZ = Character->GetVelocity().Z;

			(VelocityZ >= 750.0f || VelocityZ <= -700.0f) ? bIsHardFalling = true : bIsHardFalling = false;
		}
	}
}
