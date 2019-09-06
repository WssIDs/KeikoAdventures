// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "InteractedActor.h"
#include "KACharacter.generated.h"

USTRUCT(BlueprintType)
struct FFIKData
{
	GENERATED_BODY()

	UPROPERTY(Category = FootIK, BlueprintReadWrite)
	FVector OffsetBS;

	UPROPERTY(Category = FootIK, BlueprintReadWrite)
	FVector OffsetWS;

	UPROPERTY(Category = FootIK, BlueprintReadWrite)
	FTransform FootTransformWS;

	UPROPERTY(Category = FootIK, BlueprintReadWrite)
	float Aplha;

	FFIKData()
	{

	}

	FFIKData(FVector offsetbs, FVector offsetws, FTransform foottransformws, float alpha)
	{
		OffsetBS = offsetbs;
		OffsetWS = offsetws;
		FootTransformWS = foottransformws;
		Aplha = alpha;
	}
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterDiedSignature);

UCLASS()
class KEIKOADVENTURES_API AKACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKACharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

private:

	/** spring arm component (optional sub-object). */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

	/** camera component (optional sub-object). */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;

	/** Tracing Usable Actor */
	UPROPERTY(Category = UseableActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AInteractedActor* UseableActor;

	/** Set new distance for Camera */
	UPROPERTY()
	float CameraDistance;

	/** Movement Speed */
	UPROPERTY()
	float CharacterWalkSpeed;

	UPROPERTY()
	float NewWalkSpeed;

	/** use trace debug */
	UPROPERTY(Category = Debug, EditAnywhere)
	bool bFootTraceDebug;

	/** use trace debug */
	UPROPERTY(Category = Debug, EditAnywhere)
	bool bUseableTraceDebug;

	UPROPERTY(Category = FootIK, EditDefaultsOnly)
	bool bProcessFootIK;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Serialize(FArchive& Ar) override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	/*	calculation of the foot position relative to the floor
	 *	SocketName - Bone name or socket name a skeletal mesh
	 *	Distance - max distance for tracing
	 *	OutOffsetBS - bone space offset
	 *	OutOffsetWS - world space offset
	 *	OutFootTransformWS - world transform of bone
	 *	return Alpha for anim graph
	 */
	virtual FFIKData FootIKProcess(const FName SocketName, const float Distance);
	
	/*	Get Useable when tracing Actor
	*	Distance - maxdistance for tracing
	*	
	*/
	virtual AInteractedActor* UseableActorProcess(const float Distance);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Name of the ShoesComponent. Use this name if you want to prevent creation of the component (with ObjectInitializer.DoNotCreateDefaultSubobject). */
	static FName SpringArmComponentName;

	/** Name of the ShoesComponent. Use this name if you want to prevent creation of the component (with ObjectInitializer.DoNotCreateDefaultSubobject). */
	static FName CameraComponentName;

	/** Returns SprintArm subobject **/
	class USpringArmComponent* GetSpringArm() const;

	/** Returns Camera subobject **/
	class UCameraComponent* GetCamera() const;

	/** Return tracing UseableActor */
	class AInteractedActor* GetUseableActor() const;

	///  TEST ///
	FFIKData FootIKTest;

	/** Don't move when true */
	UPROPERTY(Category = Movement, EditDefaultsOnly, BlueprintReadWrite)
	bool bDisableMovement;

	/** When move Forward/Backward */
	UPROPERTY(Category = Movement, VisibleDefaultsOnly, BlueprintReadWrite)
	bool bMoveForward;

	/** When move Right/Left */
	UPROPERTY(Category = Movement, VisibleDefaultsOnly, BlueprintReadWrite)
	bool bMoveRight;

	/** When is moving */
	UPROPERTY(Category = Movement, VisibleDefaultsOnly, BlueprintReadWrite)
	bool bMoving;

	/** When Fast running */
	UPROPERTY(Category = Movement, VisibleDefaultsOnly, BlueprintReadWrite)
	bool bFastRun;

	/** min distance camera */
	UPROPERTY(Category = Camera, EditDefaultsOnly, BlueprintReadWrite, meta = (UIMin = "50.0", UIMax = "150.0"))
	float MinCameraDistance = 100.0f;

	/** max distance camera */
	UPROPERTY(Category = Camera, EditDefaultsOnly, BlueprintReadWrite, meta = (UIMin = "250.0", UIMax = "350.0"))
	float MaxCameraDistance = 300.0f;

	/** max character speed */
	UPROPERTY(Category = Movement, EditDefaultsOnly, BlueprintReadWrite)
	float MaxCharacterWalkSpeed = 700.0f;

	/*  FootIK*/

	/** bone or socket name for left foot */
	UPROPERTY(Category = FootIK, EditDefaultsOnly, BlueprintReadWrite, meta = (EditCondition = "bProcessFootIK"))
	FName LeftFootSocket;

	/** bone or socket name for right foot */
	UPROPERTY(Category = FootIK, EditDefaultsOnly, BlueprintReadWrite, meta = (EditCondition = "bProcessFootIK"))
	FName RightFootSocket;

	UPROPERTY(Category = FootIK, EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bProcessFootIK"))
	float FootInterpSpeed;

	UPROPERTY(Category = FootIK, EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bProcessFootIK"))
	float HipInterpSpeed;

	/** Distance for trace Start from character center */
	UPROPERTY(Category = FootIK, EditDefaultsOnly, BlueprintReadWrite, meta = (EditCondition = "bProcessFootIK"))
	float FootIteractionDistance = 100.0f;

	/** Arrays type actor to trace */
	UPROPERTY(Category = FootIK, EditDefaultsOnly, BlueprintReadWrite, meta = (EditCondition = "bProcessFootIK"))
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceFilter;

	/** Distance for trace Start from camera position */
	UPROPERTY(Category = Useable, EditDefaultsOnly, BlueprintReadWrite)
		float UseableIteractionDistance = 300.0f;

	/** Arrays type actor to trace */
	UPROPERTY(Category = Useable, EditDefaultsOnly, BlueprintReadWrite)
		TArray<TEnumAsByte<EObjectTypeQuery>> UseableFilter;

	UPROPERTY(Category = Stats, EditAnywhere, BlueprintReadWrite, SaveGame)
		float Health;

	UPROPERTY(Category = Stats, EditAnywhere, BlueprintReadWrite, SaveGame)
		float HealthMax;

	UPROPERTY(Category = Stats, EditAnywhere, BlueprintReadWrite)
		float HealthInterpolatedSpeed;

	UPROPERTY(Category = Stats, EditDefaultsOnly, BlueprintReadWrite,SaveGame)
		float Stamina;

	UPROPERTY(Category = Stats, EditDefaultsOnly, BlueprintReadWrite, SaveGame)
		float Magic;

	UPROPERTY(Category = Death, EditDefaultsOnly, BlueprintReadWrite)
	bool bIsDied;

	/**
	* Apply damage to this actor.
	* @see https://www.unrealengine.com/blog/damage-in-ue4
	* @param DamageAmount		How much damage to apply
	* @param DamageEvent		Data package that fully describes the damage received.
	* @param EventInstigator	The Controller responsible for the damage.
	* @param DamageCauser		The Actor that directly caused the damage (e.g. the projectile that exploded, the rock that landed on you)
	* @return					The amount of damage actually applied.
	*/
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


	/* Delegates */

	UFUNCTION()
		void Died();

	/** Called when the actor is died */
	UPROPERTY(BlueprintAssignable, Category = "Game|Event")
		FCharacterDiedSignature OnDied;


	FTimerHandle HealthTimer;
	FTimerHandle HealthTimerRecovery;
	FTimerDelegate TimerRecoveryDelegale;

	FTimerHandle StaminaTimerSprint;

	FTimerHandle RespawnTimer;

	float HealthTo;

	UFUNCTION()
		void Respawn();

	UFUNCTION()
		void HealthTakeDamageUpdate();

	UFUNCTION()
		void HealthRecoveryUpdate();

	UFUNCTION()
		void StaminaSprintUpdate();

	UFUNCTION()
		void CalculateCharacterStats();

	UPROPERTY(Category = Attack, EditAnywhere, BlueprintReadWrite)
		int32 TestInt;

public :

	UFUNCTION(BlueprintCallable)
	void MoveForward(float Value);

	UFUNCTION(BlueprintCallable)
	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable)
	void CameraZoom(float Value);

	UFUNCTION(BlueprintCallable, Category = "Pawn|Character")
	virtual void InitJump();

	UFUNCTION(BlueprintCallable)
	void StartFastRun();

	UFUNCTION(BlueprintCallable)
	void StopFastRun();

	/* Interact actor */
	UFUNCTION(BlueprintCallable)
	void Interact();

	void ReplayGame();

	UFUNCTION(BlueprintCallable)
	void Resurrect();

	UFUNCTION(Category = Physics,BlueprintCallable)
	void InitRagdoll();

	UFUNCTION(Category = Physics, BlueprintCallable)
	void StopRagdoll();

	UFUNCTION(BlueprintCallable)
	bool IsProcessFootIK() const { return bProcessFootIK; }

	UFUNCTION(BlueprintCallable)
	void SetEnableProcessFootIK(bool bProcess);

	UFUNCTION(BlueprintCallable)
	void ToggleProcessFootIK();
};


// Inlines

/** Returns SpringArm subobject **/
FORCEINLINE USpringArmComponent* AKACharacter::GetSpringArm() const { return SpringArm; }

/** Returns Camera subobject **/
FORCEINLINE UCameraComponent* AKACharacter::GetCamera() const { return Camera; }

/** Returns Useable Actor **/
FORCEINLINE AInteractedActor* AKACharacter::GetUseableActor() const { return UseableActor; }

DECLARE_LOG_CATEGORY_EXTERN(KACharacterLog, Log, All);