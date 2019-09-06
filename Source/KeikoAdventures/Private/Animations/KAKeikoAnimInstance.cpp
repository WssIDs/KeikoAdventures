// Fill out your copyright notice in the Description page of Project Settings.

#include "KAKeikoAnimInstance.h"
#include "KAKeikoCharacter.h"
#include "HighResScreenshot.h"
#include <ImageUtils.h>


DEFINE_LOG_CATEGORY(KAKeikoAnimInstanceLog);


void UKAKeikoAnimInstance::NativeBeginPlay()
{
	if (Character)
	{
		AKAKeikoCharacter* Keiko = Cast<AKAKeikoCharacter>(Character);

		if (Keiko)
		{
			if (Keiko->InitPlayAnimation)
			{
				Montage_Play(Keiko->InitPlayAnimation);
			}
		}
	}
}

void UKAKeikoAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (Character)
	{
		Character = Cast<AKAKeikoCharacter>(Character);
	}
}

void UKAKeikoAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character)
	{
		bIsDied = Character->bIsDied;

		if (!bIsDied)
		{
			FRotator DeltaRot = Character->GetBaseAimRotation() - Character->GetActorRotation();

			Roll = DeltaRot.Roll;
			Pitch = DeltaRot.Pitch;
			Yaw = DeltaRot.Yaw;

			float YawDeltaNeed = 0.0f;

			if (DeltaSeconds > 0)
			{
				YawDeltaNeed = ((RotationLastTick - Character->GetActorRotation()).Yaw) / (DeltaSeconds * 7.0f);
			}

			else
			{
				YawDeltaNeed = ((RotationLastTick - Character->GetActorRotation()).Yaw) / (0.1f * 7.0f);
			}

			YawDelta = FMath::FInterpTo(YawDelta, YawDeltaNeed, DeltaSeconds, 6.0f);

			RotationLastTick = Character->GetActorRotation();

			(GetCurveValue("FullBody") > 0) ? bIsFullBody = true : bIsFullBody = false;
		}
	}
}

void UKAKeikoAnimInstance::AnimNotify_SaveAttack()
{
	UE_LOG(KAKeikoAnimInstanceLog, Log, TEXT("Anim Notify SaveAttack"));

	if (Character)
	{
		AKAKeikoCharacter * Keiko = Cast<AKAKeikoCharacter>(Character);

		if (Keiko)
		{
			Keiko->ComboAttackSave();
			
			UE_LOG(KAKeikoAnimInstanceLog, Log, TEXT("ComboAttack"));
		}
	}
}

void UKAKeikoAnimInstance::AnimNotify_ResetCombo()
{
	UE_LOG(KAKeikoAnimInstanceLog, Log, TEXT("Anim Notify ResetCombo"));

	if (Character)
	{
		AKAKeikoCharacter * Keiko = Cast<AKAKeikoCharacter>(Character);

		if (Keiko)
		{
			Keiko->ResetCombo();
			UE_LOG(KAKeikoAnimInstanceLog, Log, TEXT("ResetCombo"));
		}
	}
}
