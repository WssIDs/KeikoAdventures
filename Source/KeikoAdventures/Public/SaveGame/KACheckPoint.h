// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include <Components/BillboardComponent.h>
#include "KACheckPoint.generated.h"

UCLASS()
class KEIKOADVENTURES_API AKACheckPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKACheckPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(Category = CheckPoint, EditAnywhere, BlueprintReadWrite)
		USphereComponent* Collision;

	UPROPERTY(Category = CheckPoint, EditAnywhere, BlueprintReadWrite)
		UBillboardComponent* Icon;
	
};

DECLARE_LOG_CATEGORY_EXTERN(CheckPointLog, Log, All);
