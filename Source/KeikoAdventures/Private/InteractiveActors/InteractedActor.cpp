// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractedActor.h"
#include "Kismet/GameplayStatics.h"
#include "KAGameMode.h"
#include "Misc/Timespan.h"

DEFINE_LOG_CATEGORY(InteractedActorLog);


// Sets default values
AInteractedActor::AInteractedActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractedActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractedActor::Interact()
{
	InteractItem();
}		
