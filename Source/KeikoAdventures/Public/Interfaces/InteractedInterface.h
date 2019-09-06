// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractedInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractedInterface : public UInterface
{
	GENERATED_BODY()

public:
};

/**
 * 
 */
class KEIKOADVENTURES_API IInteractedInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void Interact() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interacted")
		FString GetItemName();
	
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
*
*/
class KEIKOADVENTURES_API IItemInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void ChangeScore() = 0;
};
