// Fill out your copyright notice in the Description page of Project Settings.

#include "KACharacter.h"
#include "DrawDebugHelpers.h"
#include "Interfaces/InteractedInterface.h"
#include "KAAnimInstance.h"
#include "Animation/AnimInstance.h"
#include "KAGame.h"
#include "KAGameInstance.h"
#include "Engine/EngineTypes.h"
#include "KAPlayerController.h"
#include "KAPlayerState.h"
#include <Kismet/GameplayStatics.h>
#include "KAHUD.h"
#include "KAGameplayStatics.h"
#include "Runtime/Core/Public/Serialization/Archive.h"

DEFINE_LOG_CATEGORY(KACharacterLog);


FName AKACharacter::SpringArmComponentName(TEXT("SpringArm0"));
FName AKACharacter::CameraComponentName(TEXT("Camera0"));

// Sets default values
AKACharacter::AKACharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	
	// Settings CaplsueComponent
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 90.0f);

	// Settings CharacterMovement Component
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 450.0f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 200.0f;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;


	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));


	/*
	 *	Camera Settings
	 */

	 // Create a spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(AKACharacter::SpringArmComponentName);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 50.0f);
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetupAttachment(RootComponent);

	// Create camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(AKACharacter::CameraComponentName);
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);


	CameraDistance = SpringArm->TargetArmLength;
	CharacterWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	NewWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;


	FootIKTest.Aplha = 1.0f;

	Health = 110.0f;
	HealthMax = 110.0f;

	Magic = 100.0f;
	Stamina = 100.0f;

	OnDied.AddDynamic(this, &AKACharacter::Died);

}

void AKACharacter::Resurrect()
{
	if (bIsDied)
	{
		bIsDied = false;

		StopRagdoll();

		Health = HealthMax;

		UE_LOG(KACharacterLog, Log, TEXT("Character is alive, Health = %d"), Health);
	}
}

void AKACharacter::InitRagdoll()
{
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));

	// Ragdoll
	GetMesh()->SetPhysicsBlendWeight(1.0);
}

void AKACharacter::StopRagdoll()
{
	/* Disable all collision on capsule */
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();

	// Îñòàíîâêà Ragdolls
	GetMesh()->SetPhysicsBlendWeight(0.0f);
	GetMesh()->SetSimulatePhysics(false);

	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

	FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);

	// Ïåðåìåùåíèå êîìïîíåíòà â íà÷àëüíîå ïîëîæåíèå
	GetMesh()->AttachToComponent(CapsuleComp, Rules);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));


}

// Called when the game starts or when spawned
void AKACharacter::BeginPlay()
{
	Super::BeginPlay();

	UKAGameInstance* GI = Cast<UKAGameInstance>(GetGameInstance());
	if (GI)
	{
		if (GI->LoadSaveGameInstance)
		{
			UKAGameplayStatics::ActorLoader(this, GI->LoadSaveGameInstance->CharacterData);
			UE_LOG(KACharacterLog, Error, TEXT("Character Data - Loaded"));
		}
		else
		{
			UE_LOG(KACharacterLog, Error, TEXT("LoadGameInstance - null"));
		}
	}
	else
	{
		UE_LOG(KACharacterLog, Error, TEXT("GI - null"));
	}

	UE_LOG(KACharacterLog,Warning,TEXT("KACharacter Begin Play"));

	CalculateCharacterStats();
}


void AKACharacter::Serialize(FArchive& Ar)
{
	Ar << TestInt;
	
	Super::Serialize(Ar);
}

void AKACharacter::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	UKAGameInstance* GI = Cast<UKAGameInstance>(GetGameInstance());

	if (GI)
	{
		if (GI->LoadSaveGameInstance)
		{
			GI->LoadSaveGameInstance->CharacterData = UKAGameplayStatics::ActortSaver(this);
			UE_LOG(KACharacterLog, Error, TEXT("Character Data - Save"));
		}
		else
		{
			UE_LOG(KACharacterLog, Error, TEXT("LoadSaveGameInstance error"));
		}
	}

	UE_LOG(KACharacterLog, Error, TEXT("Character EndPlay"));
	
	Super::EndPlay(EndPlayReason);
}

FFIKData AKACharacter::FootIKProcess(const FName SocketName,const float Distance)
{
	FTransform BoneTransform;
	FVector ZMinusVector = FVector(0.0f, 0.0f, -1.0f);

	if (GetMesh()->IsValidLowLevel())
	{
		BoneTransform = GetMesh()->GetSocketTransform(SocketName, RTS_World);

		FHitResult* HitResult = new FHitResult();
		FVector Start = FVector(BoneTransform.GetLocation().X, BoneTransform.GetLocation().Y, GetActorLocation().Z);
		FVector End = Start + (ZMinusVector*Distance);

		FCollisionQueryParams* CollisionTraceParams = new FCollisionQueryParams(TEXT("FootTrace"), true, this);
		FCollisionObjectQueryParams* ObjectTraceParams = new FCollisionObjectQueryParams(TraceFilter);

		if (GetWorld()->LineTraceSingleByObjectType(*HitResult, Start, End, *ObjectTraceParams,*CollisionTraceParams))
		{
			if (bFootTraceDebug)
			{
				DrawDebugLine(GetWorld(), Start, HitResult->ImpactPoint, FColor::Red, false, 10.f, ESceneDepthPriorityGroup::SDPG_MAX, 2.0f);
				DrawDebugPoint(GetWorld(), HitResult->ImpactPoint - FVector(0.0f, 0.0f, -2.0f), 25.0f, FColor::Red, false, 10.0f, ESceneDepthPriorityGroup::SDPG_MAX);
				DrawDebugLine(GetWorld(), HitResult->ImpactPoint, End, FColor::Green, false, 10.f, ESceneDepthPriorityGroup::SDPG_MAX, 2.0f);
				UE_LOG(KACharacterLog, Log, TEXT("Hit Actor - %s"), *HitResult->Actor->GetName());
				UE_LOG(KACharacterLog, Log, TEXT("Hit Component - %s"), *HitResult->Component->GetName());
			}

			FVector HitOffset = HitResult->Location - (Start + (ZMinusVector*GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));

			return FFIKData(BoneTransform.Inverse().TransformVectorNoScale(HitOffset), HitOffset, BoneTransform, 1.0f);
		}
	}

	return FFIKData(FVector(0.0f,0.0f,0.0f),FVector(0.0f,0.0f,0.0f),BoneTransform,0.0f);
}

AInteractedActor* AKACharacter::UseableActorProcess(const float Distance)
{
	FHitResult* HitResult = new FHitResult();
	FVector Start = Camera->GetComponentLocation() + Camera->GetForwardVector()*SpringArm->TargetArmLength;
	FVector End = Start + (Camera->GetForwardVector()*Distance);

	FCollisionQueryParams* CollisionTraceParams = new FCollisionQueryParams(TEXT("UseableTrace"), true, this);
	FCollisionObjectQueryParams* ObjectTraceParams = new FCollisionObjectQueryParams(UseableFilter);

	if (GetWorld()->LineTraceSingleByObjectType(*HitResult, Start, End, *ObjectTraceParams, *CollisionTraceParams))
	{
		if(bUseableTraceDebug)
		{
			DrawDebugLine(GetWorld(), Start, HitResult->ImpactPoint, FColor::Red, false, 10.f, 0, 2.0f);
			DrawDebugPoint(GetWorld(), HitResult->ImpactPoint - FVector(0.0f, 0.0f, -2.0f), 25.0f, FColor::Red, false, 10.0f, 0);
			DrawDebugLine(GetWorld(), HitResult->ImpactPoint, End, FColor::Green, false, 10.f, 0, 2.0f);
			UE_LOG(KACharacterLog, Log, TEXT("Hit Actor - %s"), *HitResult->Actor->GetName());
		}

		return Cast<AInteractedActor>(HitResult->GetActor());
	}

	return nullptr;
}

// Called every frame
void AKACharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FFIKData LeftFootIKData;
	FFIKData RightFootIKData;

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, CameraDistance, DeltaTime, 20.0f);

	if (!bIsDied)
	{
		if (!bDisableMovement)
		{
			(bMoveForward == true || bMoveRight == true) ? bMoving = true : bMoving = false;
			GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(GetCharacterMovement()->MaxWalkSpeed, NewWalkSpeed, DeltaTime, 20);

			UKAAnimInstance* AnimInstance = Cast<UKAAnimInstance>(GetMesh()->GetAnimInstance());

			if (AnimInstance->IsValidLowLevel())
			{
				if (bProcessFootIK)
				{

					LeftFootIKData = FootIKProcess(LeftFootSocket, FootIteractionDistance);
					RightFootIKData = FootIKProcess(RightFootSocket, FootIteractionDistance);

					if (!GetCharacterMovement()->IsFalling())
					{
						FVector hoffset = FVector(0.0f, 0.0f, FMath::Min(LeftFootIKData.OffsetWS.Z, RightFootIKData.OffsetWS.Z));

						AnimInstance->HipOffset = FMath::VInterpTo(AnimInstance->HipOffset, hoffset, DeltaTime, HipInterpSpeed);

						AnimInstance->LeftFootEffectorLocation = FMath::VInterpTo(AnimInstance->LeftFootEffectorLocation, LeftFootIKData.FootTransformWS.Inverse().TransformVectorNoScale(LeftFootIKData.OffsetWS - hoffset), DeltaTime, FootInterpSpeed);
						AnimInstance->RightFootEffectorLocation = FMath::VInterpTo(AnimInstance->RightFootEffectorLocation, RightFootIKData.FootTransformWS.Inverse().TransformVectorNoScale(RightFootIKData.OffsetWS - hoffset), DeltaTime, FootInterpSpeed);
						AnimInstance->LeftAlpha = LeftFootIKData.Aplha;
						AnimInstance->RightAlpha = RightFootIKData.Aplha;

						AnimInstance->HipAlpha = FMath::Min(LeftFootIKData.Aplha, RightFootIKData.Aplha);
					}
					else
					{
						AnimInstance->LeftAlpha = 0.0f;
						AnimInstance->RightAlpha = 0.0f;
						AnimInstance->HipAlpha = 0.0f;
					}
				}
				else
				{
					AnimInstance->LeftAlpha = 0.0f;
					AnimInstance->RightAlpha = 0.0f;
					AnimInstance->HipAlpha = 0.0f;
				}
			}
		}
	}
	else
	{
		UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
		CapsuleComp->SetWorldLocation(GetMesh()->GetBoneLocation(TEXT("pelvis")));
	}

	UseableActor = UseableActorProcess(UseableIteractionDistance);

}

// Called to bind functionality to input
void AKACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//  Camera
	PlayerInputComponent->BindAxis("CameraZoom", this, &AKACharacter::CameraZoom);

	// Character
	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &AKACharacter::InitJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AKACharacter::StopJumping);
	PlayerInputComponent->BindAction("FastRun", IE_Pressed, this, &AKACharacter::StartFastRun);
	PlayerInputComponent->BindAction("FastRun", IE_Released, this, &AKACharacter::StopFastRun);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AKACharacter::Interact);
	
	// Bind for MiniGame
	//PlayerInputComponent->BindAction("ReplayGame", IE_Pressed, this, &AKACharacter::ReplayGame);
	PlayerInputComponent->BindAction("Resurrect", IE_Pressed, this, &AKACharacter::Resurrect);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AKACharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AKACharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AKACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AKACharacter::AddControllerPitchInput);

}


float AKACharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = DamageAmount;
	GetWorldTimerManager().ClearTimer(HealthTimerRecovery);

	Super::TakeDamage(ActualDamage, DamageEvent, EventInstigator, DamageCauser);

	if (!bIsDied)
	{
		UE_LOG(KACharacterLog, Log, TEXT("Character take %lf, Health = %lf"), ActualDamage, Health);

		if(FMath::IsNearlyZero(Health - ActualDamage,0.1f) || (Health - ActualDamage) < 0)
		{
			HealthTo = 0;
		}
		else
		{
			HealthTo = Health - ActualDamage;
		}

		GetWorldTimerManager().SetTimer(HealthTimer, this, &AKACharacter::HealthTakeDamageUpdate, GetWorld()->GetDeltaSeconds(), true);

		TimerRecoveryDelegale.BindUFunction(this, TEXT("HealthRecoveryUpdate"));
		GetWorldTimerManager().SetTimer(HealthTimerRecovery, this, &AKACharacter::HealthRecoveryUpdate, GetWorld()->GetDeltaSeconds(), true, 5);
	}

	return ActualDamage;
}

void AKACharacter::Died()
{
	bIsDied = true;
	bMoveForward = false;
	bMoveRight = false;
	bMoving = false;

	InitRagdoll();

	UE_LOG(KACharacterLog, Error, TEXT("Character is died, Health = %d"), Health);

	GetWorldTimerManager().SetTimer(RespawnTimer, this, &AKACharacter::Respawn, GetWorld()->GetDeltaSeconds(), false, 3.0f);
}

void AKACharacter::Respawn()
{
	UKAGameInstance* GI = Cast<UKAGameInstance>(GetGameInstance());
	if (GI)
	{
		AKAPlayerController* KAPC = Cast<AKAPlayerController>(Controller);
		if (KAPC)
		{
			AKAHUD* KAHUD = Cast<AKAHUD>(KAPC->MyHUD);
			if (KAHUD)
			{
				KAHUD->UserWidget->RemoveFromParent();
			}
		}

		UGameplayStatics::OpenLevel(this, GI->LevelName, false);
	}
}

void AKACharacter::HealthTakeDamageUpdate()
{
	if (Health != HealthTo)
	{
		Health = FMath::FInterpTo(Health, HealthTo, GetWorld()->GetDeltaSeconds(), HealthInterpolatedSpeed);
		//Health-= 0.2f;
		UE_LOG(KACharacterLog, Warning, TEXT("Update Health = %lf"), Health);
	}
	else
	{
		Health = HealthTo;
		GetWorldTimerManager().ClearTimer(HealthTimer);
		UE_LOG(KACharacterLog, Log, TEXT("Clear Health Timer"));

		if (Health <= 0)
		{
			Health = 0;
			OnDied.Broadcast();
		}
	}
}

void AKACharacter::HealthRecoveryUpdate()
{
	if (!bIsDied)
	{
		if (Health != HealthMax)
		{
			Health = FMath::FInterpConstantTo(Health, HealthMax, GetWorld()->GetDeltaSeconds(), 1.0f);
			UE_LOG(KACharacterLog, Warning, TEXT("Update Health = %lf"), Health);
		}
		else
		{
			Health = HealthMax;
			GetWorldTimerManager().ClearTimer(HealthTimerRecovery);
			UE_LOG(KACharacterLog, Log, TEXT("Clear Health Revovery Timer"));
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(HealthTimerRecovery);
		UE_LOG(KACharacterLog, Log, TEXT("Clear Health Revovery Timer. Player is Died"));
	}
}

void AKACharacter::StaminaSprintUpdate()
{

	if (Stamina >= 0)
	{
		UE_LOG(KACharacterLog, Log, TEXT("Stamina Update"));
		Stamina -= 1.f;
	}
	else
	{
		Stamina = 0.0f;
		GetWorldTimerManager().ClearTimer(StaminaTimerSprint);
	}
}

void AKACharacter::CalculateCharacterStats()
{
	if (Controller)
	{
		AKAPlayerController* KAPlayerController = Cast<AKAPlayerController>(Controller);

		if (KAPlayerController)
		{
			if (KAPlayerController->PlayerState)
			{
				AKAPlayerState* KAPlayerState = Cast<AKAPlayerState>(KAPlayerController->PlayerState);

				if (KAPlayerState)
				{
					float Level = KAPlayerState->Level;

					HealthMax = 100 + Level * 10;
					//Health = HealthMax;
				}
			}
		}
	}
}

void AKACharacter::MoveForward(float Value)
{
	if (!bIsDied)
	{
		if (!bDisableMovement)
		{
			if (Controller != nullptr)
			{
				if (Value != 0.0f)
				{
					bMoveForward = true;

					// find out which way is forward
					FRotator Rotation = Controller->GetControlRotation();
					// Limit pitch when walking or falling
					if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
					{
						Rotation.Pitch = 0.0f;
					}
					// add movement in that direction
					const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
					AddMovementInput(Direction, Value);

					//UE_LOG(KACharacterLog, Log, TEXT("MoveForward true"));
				}
				else
				{
					bMoveForward = false;
					//UE_LOG(KACharacterLog, Log, TEXT("MoveForward false"));
				}
			}

		}
	}

}

void AKACharacter::MoveRight(float Value)
{
	if (!bIsDied)
	{
		if (!bDisableMovement)
		{
			if ((Controller != NULL))
			{
				if (Value != 0.0f)
				{
					bMoveRight = true;

					// find out which way is right
					const FRotator Rotation = Controller->GetControlRotation();
					const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
					// add movement in that direction
					AddMovementInput(Direction, Value);

					//UE_LOG(KACharacterLog, Log, TEXT("MoveRight true"));
				}
				else
				{
					bMoveRight = false;
					//UE_LOG(KACharacterLog, Log, TEXT("MoveRight false"));
				}
			}
		}
	}
}

void AKACharacter::CameraZoom(float Value)
{
	if (Value != 0)
	{
		float ZoomFactor = -Value * 10.f;

		CameraDistance = FMath::Clamp(CameraDistance + ZoomFactor, MinCameraDistance, MaxCameraDistance);

		//UE_LOG(KACharacterLog, Log, TEXT("CameraZoom = %f"), ZoomFactor);
	}
}

void AKACharacter::InitJump()
{
	if (!bIsDied)
	{
		if (!bDisableMovement)
		{
			if (!GetCharacterMovement()->IsFalling())
			{
				if (GetCharacterMovement()->Velocity.Size() > 0.0f)
				{
					GetCharacterMovement()->JumpZVelocity = 700.0f;
					Jump();
					//UE_LOG(KACharacterLog, Log, TEXT("Jump 700"));
				}

				else
				{
					GetCharacterMovement()->JumpZVelocity = 600.0f;
					Jump();
					//UE_LOG(KACharacterLog, Log, TEXT("Jump 600"));
				}
			}
		}
	}
}

void AKACharacter::StartFastRun()
{
	GetWorldTimerManager().ClearTimer(StaminaTimerSprint);

	if (Stamina > 0)
	{
		if (!bIsDied)
		{
			if (!bDisableMovement)
			{

				bFastRun = true;
				NewWalkSpeed = MaxCharacterWalkSpeed;
				UE_LOG(KACharacterLog, Log, TEXT("Start FastRun"));

				GetWorldTimerManager().SetTimer(StaminaTimerSprint, this, &AKACharacter::StaminaSprintUpdate, 1.0f, true, 0.0f);
			}
		}
	}
	else
	{
		Stamina = 0.0f;
	}
}

void AKACharacter::StopFastRun()
{
	bFastRun = false;
	NewWalkSpeed = CharacterWalkSpeed;
	GetWorldTimerManager().ClearTimer(StaminaTimerSprint);
	UE_LOG(KACharacterLog, Log, TEXT("Stop FastRun"));
}

void AKACharacter::Interact()
{
	if (!bIsDied)
	{
		IInteractedInterface* Interface = Cast<IInteractedInterface>(UseableActor);

		if (Interface)
		{
			Interface->Interact();
		}
	}
}

// Only for Test

void AKACharacter::ReplayGame()
{
	UKAGameInstance* GameInstance = Cast<UKAGameInstance>(GetGameInstance());

	if (GameInstance)
	{
		UE_LOG(KACharacterLog, Log, TEXT("GameInstance - %s"), *GameInstance->GetName());

		AKAGame* Game = GameInstance->GetGame();

		if (Game)
		{
			UE_LOG(KACharacterLog, Log, TEXT("Game - %s"), *Game->GetName());
			Game->Stop();
			Game->Init();
		}
	}
}


void AKACharacter::SetEnableProcessFootIK(bool bProcess)
{
	bProcessFootIK = bProcess;
}

void AKACharacter::ToggleProcessFootIK()
{
	bProcessFootIK = !bProcessFootIK;
}
