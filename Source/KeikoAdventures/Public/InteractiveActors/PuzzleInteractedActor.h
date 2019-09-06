// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActors/InteractedActor.h"
#include <Engine/StaticMesh.h>
#include <Sound/SoundCue.h>
#include "Particles/ParticleSystemComponent.h"
#include "PuzzleInteractedActor.generated.h"


UENUM(BlueprintType)
enum class EInteractedSide : uint8
{
	IS_FRONT UMETA(DisplayName = "Front"),
	IS_RIGHT UMETA(DisplayName = "Right"),
	IS_BACK UMETA(DisplayName = "Back"),
	IS_LEFT UMETA(DisplayName = "Left")
};


/**
 * 
 */
UCLASS()
class KEIKOADVENTURES_API APuzzleInteractedActor : public AInteractedActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APuzzleInteractedActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;

	UPROPERTY(Category = Settings, EditAnywhere, BlueprintReadWrite)
		TArray<APuzzleInteractedActor*> DependentActors;

	UPROPERTY()
		USceneComponent* Scene;

	UPROPERTY(Category = Settings, EditAnywhere, BlueprintReadWrite)
		EInteractedSide StartSide;

	UPROPERTY(Category = Settings, EditAnywhere, BlueprintReadWrite)
		EInteractedSide CompleteSide;

	UPROPERTY(Category = Settings, EditAnywhere, BlueprintReadWrite)
		USoundCue* InteractSound;

	UFUNCTION()
		void ChangeSide();

	UFUNCTION(Category = Interact, BlueprintCallable)
	UStaticMeshComponent* GetMeshComponent() const
	{
		return MeshComponent;
	}

	virtual void OnConstruction(const FTransform& Transform) override;
	FTimerHandle RotationTimer;

private:

	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* MeshComponent;

	UPROPERTY(Category = Particle, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* ParticleComponent;

	UFUNCTION()
		void UpdateRotation();

	UPROPERTY()
	FRotator RotationTo;
};

DECLARE_LOG_CATEGORY_EXTERN(PuzzleInteractedActorLog, Log, All);
