// Fill out your copyright notice in the Description page of Project Settings.

#include "KACheckPoint.h"
#include "KACharacter.h"
#include "KAGameInstance.h"
#include <Kismet/GameplayStatics.h>

DEFINE_LOG_CATEGORY(CheckPointLog);

// Sets default values
AKACheckPoint::AKACheckPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(RootComponent);

	RootComponent = Collision;

	Icon = CreateDefaultSubobject<UBillboardComponent>(TEXT("Icon"));
	Icon->SetupAttachment(Collision);


	Collision->OnComponentBeginOverlap.AddDynamic(this, &AKACheckPoint::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AKACheckPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKACheckPoint::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AKACharacter* KAChar = Cast<AKACharacter>(OtherActor);

		if (KAChar)
		{
			UKAGameInstance* GI = Cast<UKAGameInstance>(GetGameInstance());

			if (GI)
			{
				GI->LastCheckPoint = GetActorTransform();

				FString MapName = UGameplayStatics::GetCurrentLevelName(GetWorld());
				GI->LevelName = FName(*MapName);

				UE_LOG(CheckPointLog, Log, TEXT("Level - %s"), *MapName);
			}
		}

		UE_LOG(CheckPointLog, Log, TEXT("Overlap"));

	}
}

