// Fill out your copyright notice in the Description page of Project Settings.

#include "KAObtaclesSplineActor.h"
#include "KAPlatformComponent.h"
#include <DeclarativeSyntaxSupport.h>
#include "KACharacter.h"


DEFINE_LOG_CATEGORY(KAObtaclesSplineActorLog);

// Sets default values
AKAObtaclesSplineActor::AKAObtaclesSplineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SplineComponent->SetupAttachment(RootComponent);

	CollsionRaduis = 20.0f;
	ScaleMesh = FVector(1.0f,1.0f,1.0f);

	for (auto& Item : NewPlatforms)
	{
		USphereComponent* Collision = Cast<USphereComponent>(Item.Key);
		if (Collision)
		{
			Collision->InitSphereRadius(CollsionRaduis);
		}
	}

}

// Called when the game starts or when spawned
void AKAObtaclesSplineActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AKAObtaclesSplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKAObtaclesSplineActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AKACharacter>(OtherActor)->IsValidLowLevel())
	{
		if (OverlappedComp->IsValidLowLevel())
		{

			UE_LOG(KAObtaclesSplineActorLog, Log, TEXT("Begin Overlap - %s"), *OverlappedComp->GetName());
		}
	}
}

void AKAObtaclesSplineActor::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AKACharacter>(OtherActor)->IsValidLowLevel())
	{
		if (OverlappedComp->IsValidLowLevel())
		{
			USphereComponent* Collision = Cast<USphereComponent>(OverlappedComp);

			if (Collision->IsValidLowLevel())
			{
				if (Collision->OnComponentEndOverlap.IsBound())
				{
					Collision->OnComponentEndOverlap.Clear();
				}

				UKAPlatformComponent* Platform = *NewPlatforms.Find(Collision);

				if (Platform->IsValidLowLevel())
				{
					Platform->InitFall();
					NewPlatforms.Remove(Collision);
				}

				UE_LOG(KAObtaclesSplineActorLog, Log, TEXT("End Overlap - %s"), *OverlappedComp->GetName());
			}
		}
	}
}

void AKAObtaclesSplineActor::UpdateComponentsOnSpline()
{
	for (auto& NewPlatform : NewPlatforms)
	{
		USphereComponent* PlatformCollision = NewPlatform.Key;
		if (PlatformCollision->IsValidLowLevel())
		{
			UE_LOG(KAObtaclesSplineActorLog, Log, TEXT("Clear Binding Platfom Collision"));

			if (PlatformCollision->OnComponentBeginOverlap.IsBound())
			{
				PlatformCollision->OnComponentBeginOverlap.Clear();
			}

			if (PlatformCollision->OnComponentEndOverlap.IsBound())
			{
				PlatformCollision->OnComponentEndOverlap.Clear();
			}
			PlatformCollision->DestroyComponent();
		}

		UKAPlatformComponent* Platform = NewPlatform.Value;
		if (Platform->IsValidLowLevel())
		{
			Platform->DestroyComponent();
		}
	}

	NewPlatforms.Empty();

	if (SplineComponent->GetNumberOfSplinePoints() > 0)
	{
		for (int32 i = 0; i < SplineComponent->GetNumberOfSplinePoints(); i++)
		{
			UKAPlatformComponent* PlatformComponent = NewObject<UKAPlatformComponent>(this);
			USphereComponent* PlatformCollisionComponent;
			if (PlatformComponent->IsValidLowLevel())
			{
				PlatformComponent->RegisterComponent();

				FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative, false);
				PlatformComponent->AttachToComponent(SplineComponent, Rules);

				PlatformComponent->SetRelativeLocation(SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local));
				PlatformComponent->SetRelativeRotation(SplineComponent->GetRotationAtSplinePoint(i, ESplineCoordinateSpace::Local));
				PlatformComponent->SetRelativeScale3D(ScaleMesh);

				if (Mesh)
				{
					PlatformComponent->SetStaticMesh(Mesh);
				}

				PlatformCollisionComponent = NewObject<USphereComponent>(this);
				if (PlatformCollisionComponent->IsValidLowLevel())
				{
					PlatformCollisionComponent->RegisterComponent();
					PlatformCollisionComponent->AttachToComponent(SplineComponent, Rules);

					PlatformCollisionComponent->SetRelativeLocation(SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local));
					PlatformCollisionComponent->SetRelativeRotation(SplineComponent->GetRotationAtSplinePoint(i, ESplineCoordinateSpace::Local));

					PlatformCollisionComponent->SetGenerateOverlapEvents(true);
					PlatformCollisionComponent->InitSphereRadius(CollsionRaduis);

					UE_LOG(KAObtaclesSplineActorLog, Log, TEXT("Binding Platfom Collision"));
					PlatformCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AKAObtaclesSplineActor::OnBeginOverlap);
					PlatformCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AKAObtaclesSplineActor::OnOverlapEnd);
				}

				NewPlatforms.Add(PlatformCollisionComponent, PlatformComponent);

				UE_LOG(KAObtaclesSplineActorLog, Log, TEXT("Platform component added - %s"), *PlatformComponent->GetName());
			}
		}
	}
}

void AKAObtaclesSplineActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UpdateComponentsOnSpline();
}

#if WITH_EDITOR

void AKAObtaclesSplineActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	UpdateComponentsOnSpline();
}

void AKAObtaclesSplineActor::PostEditMove(bool bFinished)
{
	Super::PostEditMove(bFinished);
	UpdateComponentsOnSpline();
}

#endif

