// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractedInterface.h"
#include "InteractedActor.generated.h"

UCLASS()
class KEIKOADVENTURES_API AInteractedActor : public AActor, public IInteractedInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractedActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interacted")
	void InteractItem();

	UPROPERTY(Category = "Interacted", BlueprintReadWrite, EditAnywhere)
		FText Name;
};

DECLARE_LOG_CATEGORY_EXTERN(InteractedActorLog, Log, All);