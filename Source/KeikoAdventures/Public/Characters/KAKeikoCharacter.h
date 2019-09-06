// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KACharacter.h"
#include "Sound/SoundCue.h"
#include "KAKeikoCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterAttackAnimState : uint8
{
	AS_ONE,
	AS_TWO,
	AS_THREE
};

/**
 * Keiko character
 */
UCLASS()
class KEIKOADVENTURES_API AKAKeikoCharacter : public AKACharacter
{
	GENERATED_BODY()
	
public:
	AKAKeikoCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(Category = Init, EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* InitPlayAnimation;

	UPROPERTY(Category = Attack, BlueprintReadWrite, VisibleAnywhere)
	UCapsuleComponent* WeaponCapsuleComponent;

	UPROPERTY(Category = Attack, BlueprintReadWrite)
		bool SaveAttack;

	UPROPERTY(Category = Attack, BlueprintReadWrite)
		bool bIsAttacking;

	UPROPERTY(Category = Attack, EditDefaultsOnly, BlueprintReadWrite)
		USoundCue* AttackSound;

	UFUNCTION(Category = Attack, BlueprintCallable)
		void Attack();

	UFUNCTION(Category = Attack, BlueprintCallable)
		void ComboAttackSave();

	UFUNCTION(Category = Attack, BlueprintCallable)
		void ResetCombo();

	ECharacterAttackAnimState CharacterAttackAnimState;

	UPROPERTY(Category = Attack, EditDefaultsOnly, BlueprintReadWrite, EditFixedSize)
	TArray<UAnimMontage*> AttackAnimations;


	UPROPERTY(Category = Ability, BlueprintReadWrite, VisibleAnywhere)
	bool bIsTeleporting;

	UPROPERTY(Category = Ability, EditDefaultsOnly, BlueprintReadWrite)
	USoundCue* MainAbilitySound;

	UPROPERTY(Category = Ability, EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* MainAbilityAnimation;

	UFUNCTION(Category = Ability, BlueprintCallable)
	void ActionMainAbility_Start();

	UFUNCTION(Category = Ability, BlueprintCallable)
	void ActionMainAbility_Release();

	UPROPERTY(Category = Ability, BlueprintReadWrite, EditDefaultsOnly)
	float AbilityDistance;

	UPROPERTY()
	FVector LocationTo;

	FTimerHandle MainAbilityTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void ChangeAnimationAttack();

	void UpdatePosition();
 };

DECLARE_LOG_CATEGORY_EXTERN(KAKeikoCharacterLog, Log, All);
