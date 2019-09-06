// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleInteractedActor.h"
#include <Kismet/GameplayStatics.h>


DEFINE_LOG_CATEGORY(PuzzleInteractedActorLog)

APuzzleInteractedActor::APuzzleInteractedActor()
{
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Scene->SetupAttachment(RootComponent);
	RootComponent = Scene;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionProfileName(TEXT("Useable"));
	MeshComponent->SetupAttachment(RootComponent);


	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ParticleComponent->SetupAttachment(MeshComponent);
	ParticleComponent->SetRelativeLocation(FVector(65.0f, 0.0f, 170.0f));
	ParticleComponent->bAutoActivate = 0;
}

void APuzzleInteractedActor::BeginPlay()
{
	Super::BeginPlay();
	if (StartSide == CompleteSide)
	{
		ParticleComponent->ActivateSystem(true);
	}
	else
	{
		ParticleComponent->DeactivateSystem();
	}
}

void APuzzleInteractedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APuzzleInteractedActor::Interact()
{
	Super::Interact();


	ChangeSide();

	for (auto* DependentActor : DependentActors)
	{
		DependentActor->ChangeSide();
	}

	if (StartSide == CompleteSide)
	{
		UE_LOG(PuzzleInteractedActorLog, Log, TEXT("ok"));
	}
}

void APuzzleInteractedActor::ChangeSide()
{
	if (!GetWorldTimerManager().IsTimerActive(RotationTimer))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), InteractSound, GetActorLocation());

		uint8 side = (uint8)StartSide;
		side++;

		if (side <= 3)
		{
			StartSide = (EInteractedSide)side;
		}
		else
		{
			StartSide = EInteractedSide::IS_FRONT;
		}


		switch (StartSide)
		{
		case EInteractedSide::IS_FRONT:
		{
			RotationTo = FRotator(0.0f, 0.0f, 0.0f);
			GetWorldTimerManager().SetTimer(RotationTimer, this, &APuzzleInteractedActor::UpdateRotation, GetWorld()->GetDeltaSeconds(), true);
			UE_LOG(PuzzleInteractedActorLog, Log, TEXT("Front Timer"));
		}
		break;
		case EInteractedSide::IS_RIGHT:
		{
			RotationTo = FRotator(0.0f, 90.0f, 0.0f);
			GetWorldTimerManager().SetTimer(RotationTimer, this, &APuzzleInteractedActor::UpdateRotation, GetWorld()->GetDeltaSeconds(), true);
			UE_LOG(PuzzleInteractedActorLog, Log, TEXT("Right Timer"));
		}
		break;
		case EInteractedSide::IS_BACK:
		{
			RotationTo = FRotator(0.0f, 180.0f, 0.0f);
			GetWorldTimerManager().SetTimer(RotationTimer, this, &APuzzleInteractedActor::UpdateRotation, GetWorld()->GetDeltaSeconds(), true);
		}
		break;
		case EInteractedSide::IS_LEFT:
		{
			RotationTo = FRotator(0.0f, 270.0f, 0.0f);
			GetWorldTimerManager().SetTimer(RotationTimer, this, &APuzzleInteractedActor::UpdateRotation, GetWorld()->GetDeltaSeconds(), true);
		}
		break;
		default:
			break;
		}
	}
}

void APuzzleInteractedActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	switch (StartSide)
	{
	case EInteractedSide::IS_FRONT:
	{
		RotationTo = FRotator(0.0f, 0.0f, 0.0f);
	}
	break;
	case EInteractedSide::IS_RIGHT:
	{
		RotationTo = FRotator(0.0f, 90.0f, 0.0f);
	}
	break;
	case EInteractedSide::IS_BACK:
	{
		RotationTo = FRotator(0.0f, 180.0f, 0.0f);
	}
	break;
	case EInteractedSide::IS_LEFT:
	{
		RotationTo = FRotator(0.0f, 270.0f, 0.0f);
	}
	break;
	default:
		break;
	}


	MeshComponent->SetRelativeRotation(RotationTo);

	if (StartSide == CompleteSide)
	{
		ParticleComponent->ActivateSystem(true);
	}
	else
	{
		ParticleComponent->DeactivateSystem();
	}

}

void APuzzleInteractedActor::UpdateRotation()
{
	if (MeshComponent->RelativeRotation.GetNormalized().Equals(RotationTo,1.0f))
	{
		MeshComponent->SetRelativeRotation(RotationTo);
		GetWorldTimerManager().ClearTimer(RotationTimer);

		UE_LOG(PuzzleInteractedActorLog, Error, TEXT("Objet Name = %s : Complete Rot %s"), *GetName(), *MeshComponent->RelativeRotation.ToString());
		
		if (StartSide == CompleteSide)
		{
			UE_LOG(PuzzleInteractedActorLog, Error, TEXT("Objet Name = %s : Activate Particle"), *GetName());
			ParticleComponent->ActivateSystem(true);
		}
	}
	else
	{
		MeshComponent->SetRelativeRotation(FMath::RInterpConstantTo(MeshComponent->RelativeRotation, RotationTo, GetWorld()->GetDeltaSeconds(), 50.0f));

		UE_LOG(PuzzleInteractedActorLog, Warning, TEXT("Objet Name = %s : Rot %s"), *GetName(), *MeshComponent->RelativeRotation.GetNormalized().ToString());

		if (ParticleComponent->IsActive())
		{
			ParticleComponent->DeactivateSystem();
		}
	}
	
}
