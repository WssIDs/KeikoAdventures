// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActors/InteractedActor.h"
#include "KALevelTeleportActor.generated.h"

/**
 * 
 */
UCLASS()
class KEIKOADVENTURES_API AKALevelTeleportActor : public AInteractedActor
{
	GENERATED_BODY()
	
	
public:

	UPROPERTY(Category = Widget, BlueprintReadWrite)
		UUserWidget* LoadingScreenWidget;

	UPROPERTY(Category = Classes, EditAnywhere)
		TSubclassOf<UUserWidget> LoadingScreenClass;

	UPROPERTY(Category = "Interacted", BlueprintReadWrite, EditAnywhere)
		FName NextLevel;

	virtual void Interact() override;

	UFUNCTION()
		void LoadNextLevel();

	UFUNCTION()
		void LoadMainLevel();
};
