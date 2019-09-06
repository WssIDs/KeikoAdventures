// Fill out your copyright notice in the Description page of Project Settings.

#include "KAKeikoCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Async.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY(KAKeikoCharacterLog);

AKAKeikoCharacter::AKAKeikoCharacter()
{
	WeaponCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponCapsuleComponent"));
	WeaponCapsuleComponent->SetRelativeLocation(FVector(0.0f, 40.0f, 0.0f));
	WeaponCapsuleComponent->SetRelativeRotation(FRotator(0.0f,0.0f,90.0f));
	WeaponCapsuleComponent->SetupAttachment(GetMesh(), TEXT("Sword"));
	WeaponCapsuleComponent->SetCollisionProfileName(TEXT("NoCollision"));
	WeaponCapsuleComponent->SetCapsuleHalfHeight(32.0f);
	WeaponCapsuleComponent->SetCapsuleRadius(5.0f);

	AttackAnimations.AddZeroed(3);

	AbilityDistance = 5000.0f;
}

void AKAKeikoCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Keiko Character Ability
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AKAKeikoCharacter::Attack);
	PlayerInputComponent->BindAction("MainAbility", IE_Pressed, this, &AKAKeikoCharacter::ActionMainAbility_Start);
	PlayerInputComponent->BindAction("MainAbility", IE_Released, this, &AKAKeikoCharacter::ActionMainAbility_Release);
}

void AKAKeikoCharacter::Attack()
{
	if (!bIsDied)
	{
		if (!bDisableMovement)
		{
			if (bIsAttacking)
			{
				SaveAttack = true;
			}
			else
			{
				bIsAttacking = true;
				WeaponCapsuleComponent->SetCollisionProfileName(TEXT("Sword"));
				ChangeAnimationAttack();
			}
		}
	}
}

void AKAKeikoCharacter::ComboAttackSave()
{
	if (SaveAttack)
	{
		SaveAttack = false;
		ChangeAnimationAttack();
	}
	else
	{
		UE_LOG(KAKeikoCharacterLog, Log, TEXT("SaveAtack = false"));
	}
}

void AKAKeikoCharacter::ResetCombo()
{
	CharacterAttackAnimState = ECharacterAttackAnimState::AS_ONE;
	SaveAttack = false;
	bIsAttacking = false;

	WeaponCapsuleComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void AKAKeikoCharacter::ActionMainAbility_Start()
{
	if (Magic >= 10)
	{
		if (!bIsDied)
		{
			if (bMoving)
			{
				if (!bIsAttacking)
				{
					bIsTeleporting = true;

					UGameplayStatics::PlaySoundAtLocation(GetWorld(), MainAbilitySound, GetActorLocation());
					PlayAnimMontage(MainAbilityAnimation);

					LocationTo = GetActorLocation() + GetActorForwardVector() * AbilityDistance;

					Magic -= 10.0f;

					GetWorldTimerManager().SetTimer(MainAbilityTimer, this, &AKAKeikoCharacter::UpdatePosition, 0.01f, true, 0.0f);

					FTimerHandle TimerDelay;

					GetWorldTimerManager().SetTimer(TimerDelay, [this]()
					{
						UE_LOG(KAKeikoCharacterLog, Log, TEXT("Delay Character Ability"));
						ActionMainAbility_Release();
					}, 0.5f, false);

				}
			}
		}
	}
	else
	{
		Magic = 0.0f;
	}
}

void AKAKeikoCharacter::ActionMainAbility_Release()
{
	bIsTeleporting = false;
	
	GetWorldTimerManager().ClearTimer(MainAbilityTimer);
}

void AKAKeikoCharacter::UpdatePosition()
{
	TeleportTo(FMath::Lerp(GetActorLocation(),LocationTo,0.01f),GetActorRotation());
}

void AKAKeikoCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void AKAKeikoCharacter::ChangeAnimationAttack()
{
	// Play Sound At Location
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), AttackSound, GetActorLocation());

	switch (CharacterAttackAnimState)
	{
	case ECharacterAttackAnimState::AS_ONE:
	{
		UE_LOG(KAKeikoCharacterLog, Log, TEXT("Play Montage ONE"));
		CharacterAttackAnimState = ECharacterAttackAnimState::AS_TWO;
		UE_LOG(KAKeikoCharacterLog,Log,TEXT("Current State = 1"));
		// Play Montage

		PlayAnimMontage(AttackAnimations[0]);

		break;
	}
	case ECharacterAttackAnimState::AS_TWO:
	{
		UE_LOG(KAKeikoCharacterLog, Log, TEXT("Play Montage TWO"));
		CharacterAttackAnimState = ECharacterAttackAnimState::AS_THREE;
		UE_LOG(KAKeikoCharacterLog, Log, TEXT("Current State = 2"));
		// Play Montage

		PlayAnimMontage(AttackAnimations[1]);

		break;
	}
	case ECharacterAttackAnimState::AS_THREE:
	{
		UE_LOG(KAKeikoCharacterLog, Log, TEXT("Play Montage THREE"));
		CharacterAttackAnimState = ECharacterAttackAnimState::AS_ONE;
		UE_LOG(KAKeikoCharacterLog, Log, TEXT("Current State = 0"));
		// Play Montage

		PlayAnimMontage(AttackAnimations[2]);

		break;
	}
	}
}

