// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "KAPlatformComponent.h"
#include <Components/SphereComponent.h>
#include <TransformCalculus3D.h>
#include "KAObtaclesSplineActor.generated.h"

UCLASS()
class KEIKOADVENTURES_API AKAObtaclesSplineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKAObtaclesSplineActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = Test, EditAnywhere, BlueprintReadWrite)
		UStaticMesh* Mesh;

	UPROPERTY(Category = Test, EditAnywhere, BlueprintReadWrite)
		FVector ScaleMesh;

	UPROPERTY(Category = Test, EditAnywhere, BlueprintReadWrite)
		float CollsionRaduis;

	UPROPERTY(Category = "Test", EditAnywhere, BlueprintReadWrite)
		TMap<USphereComponent*, UKAPlatformComponent*> NewPlatforms;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	UPROPERTY(Category = "Test", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USplineComponent* SplineComponent;

	UPROPERTY()
		USceneComponent * Scene;

	void UpdateComponentsOnSpline();

	virtual void OnConstruction(const FTransform& Transform) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	/** Called after an actor has been moved in the editor */
	virtual void PostEditMove(bool bFinished);

#endif

};


DECLARE_LOG_CATEGORY_EXTERN(KAObtaclesSplineActorLog, Log, All);