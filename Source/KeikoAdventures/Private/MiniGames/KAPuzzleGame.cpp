// Fill out your copyright notice in the Description page of Project Settings.

#include "KAPuzzleGame.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "KAGameInstance.h"
#include "KACharacter.h"
#include "KAPlayerState.h"


DEFINE_LOG_CATEGORY(PuzzleGameLog);

// Sets default values
AKAPuzzleGame::AKAPuzzleGame()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;


	Distance = 300.f;
	DefaultSeconds = 15.0f;
	ActiveColor = FLinearColor::Green;
	InnactiveColor = FLinearColor::Red;

	TileScale = FVector(1.0f, 1.0f, 1.0f);
}

void AKAPuzzleGame::Construct()
{
	UE_LOG(PuzzleGameLog, Log, TEXT("PuzzleGame - Construct"));

	RestartGame();

	int32 NumTiles = CountTileX * CountTileY;

	for (int32 i = 0; i < NumTiles; i++)
	{
		float Xpos = (float)(i % CountTileY * (Distance + TileOffset));
		float YPos = (float)(i / CountTileY * (Distance + TileOffset));

		FTransform TileTransform = FTransform(FRotator(0.0f, 0.0f, 0.f), FVector(Xpos, YPos, 0.0f), FVector(1.0f, 1.0f, 1.0f));

		UStaticMesh* Mesh = nullptr;

		if (PlaneMeshes.Num() > 0)
		{
			int32 RandNumber = FMath::RandRange(0, PlaneMeshes.Num() - 1);

		 	Mesh = PlaneMeshes[RandNumber];
		}

		if (Mesh)
		{
			UStaticMeshComponent* PlaneMeshComponent = NewObject<UStaticMeshComponent>(this);

			if (PlaneMeshComponent)
			{
				PlaneMeshComponent->bAutoRegister = true;

				PlaneMeshComponent->SetStaticMesh(Mesh);
				PlaneMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, NAME_None);
				PlaneMeshComponent->SetRelativeTransform(TileTransform);
				PlaneMeshComponent->SetRelativeScale3D(TileScale);
				PlaneMeshComponent->RegisterComponent();

				if (PlaneMeshComponent->IsRegistered())
				{
					StaticMeshObjects.Add(PlaneMeshComponent);

					FTileData TD;

					if (PlaneMaterial->IsValidLowLevel())
					{
						UMaterialInstanceDynamic* MatInst = UMaterialInstanceDynamic::Create(PlaneMaterial, this);
						//UMaterialInstanceDynamic* MatInst = PlaneMeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, Mesh->GetMaterial(0));
						if (MatInst)
						{
							TD.MI = MatInst;
							TD.bActivated = FMath::RandBool();
							TD.countSteps = 0;

							if (!TD.bActivated)
							{
								MatInst->SetVectorParameterValue("RockTint", InnactiveColor);
								countInnactivated++;
							}
							else
							{
								MatInst->SetVectorParameterValue("RockTint", ActiveColor);
								countActivated++;
							}

							PlaneMeshComponent->SetMaterial(0, MatInst);
						}
						else
						{
							UE_LOG(PuzzleGameLog, Error, TEXT("MatInst is not valid"));
						}
					}
					else
					{
						UE_LOG(PuzzleGameLog, Error, TEXT("PlaneMaterial is not valid"));
					}

					UBoxComponent* CollisionBoxComponent = NewObject<UBoxComponent>(this);

					if (CollisionBoxComponent)
					{
						CollisionBoxComponent->bAutoRegister = true;
						CollisionBoxComponent->SetGenerateOverlapEvents(true);
						//CollisionBoxComponent->bGenerateOverlapEvents = true;
						//CollisionBoxComponent->SetCollisionObjectType(TEXT("MinigameTrigger"));
						CollisionBoxComponent->SetCollisionProfileName("TilePlane");
						CollisionBoxComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, NAME_None);
						CollisionBoxComponent->SetRelativeTransform(TileTransform);
						CollisionBoxComponent->SetBoxExtent(FVector(Distance / 2, Distance / 2, Distance), true);
						CollisionBoxComponent->RegisterComponent();

						if (CollisionBoxComponent->IsRegistered())
						{
							UE_LOG(PuzzleGameLog, Log, TEXT("Add Collision Component - %s"), *CollisionBoxComponent->GetName());
							CollisionObjects.Add(CollisionBoxComponent, TD);
						}
						else
						{
							UE_LOG(PuzzleGameLog, Error, TEXT("CollisionBoxComponent is not registered"));
						}
					}
					else
					{
						UE_LOG(PuzzleGameLog, Error, TEXT("CollisionBoxComponent is not valid"));
					}
				}
				else
				{
					UE_LOG(PuzzleGameLog, Error, TEXT("PlaneMeshComponent is not registered"));
				}
			}
			else
			{
				UE_LOG(PuzzleGameLog, Error, TEXT("PlaneMeshComponent is not valid"));
			}
		}
		else
		{
			UE_LOG(PuzzleGameLog, Error, TEXT("PlaneMesh is not valid"));
		}
	}

	if (bCollision)
	{
		Collision = NewObject<UBoxComponent>(this);

		if (Collision->IsValidLowLevel())
		{
			Collision->SetCollisionProfileName("BlockAll");
			Collision->RegisterComponent();

			float tileDist = Distance + TileOffset;
			FVector planeSize;

			if (PlaneMesh->IsValidLowLevel())
			{
				planeSize = PlaneMesh->GetBounds().GetBox().GetSize();
			}

			Collision->AttachToComponent(Scene, FAttachmentTransformRules::KeepRelativeTransform, NAME_None);

			Collision->SetRelativeLocation(FVector((CountTileY - 1) * tileDist / 2.0f, (CountTileX - 1) * tileDist / 2.0f, 0.0f));
			Collision->SetBoxExtent(FVector((CountTileY * tileDist - TileOffset) / 2.0f, (CountTileX * tileDist - TileOffset) / 2.0f, planeSize.Z / 2.0f * TileScale.Z), true);
		}
	}
}

// Called when the game starts or when spawned
void AKAPuzzleGame::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AKAPuzzleGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKAPuzzleGame::Init()
{
	Super::Init();
}

void AKAPuzzleGame::Start()
{
	Super::Start();

	for (auto& Item : CollisionObjects)
	{
		UBoxComponent* Component = Cast<UBoxComponent>(Item.Key);

		if (Component)
		{
			UE_LOG(PuzzleGameLog, Log, TEXT("Binding"));
			Component->OnComponentBeginOverlap.AddDynamic(this, &AKAPuzzleGame::OnBeginOverlap);

		}
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PC)
	{
		PC->bShowMouseCursor = false;
		const FInputModeGameOnly InputMode = FInputModeGameOnly();
		PC->SetInputMode(InputMode);

		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
}

void AKAPuzzleGame::GenerateGame(int32 countX, int32 countY, int32 offset)
{
	CountTileX = countX;
	CountTileY = countY;
	TileOffset = offset;

	Construct();

}

void AKAPuzzleGame::GenerateGameWithTeleportPlayer(int32 countX, int32 countY, int32 offset, FVector location)
{
	
	GenerateGame(countX, countY, offset);

	AKACharacter* Keiko = Cast<AKACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Keiko->IsValidLowLevel())
	{
		Keiko->TeleportTo(location, Keiko->GetActorRotation());
	}
}

void AKAPuzzleGame::Replay()
{
	GenerateGame(CountTileX, CountTileY, TileOffset);
	Start();
}

void AKAPuzzleGame::Stop()
{
	Super::Stop();
}

void AKAPuzzleGame::ScoreChanged(int32 inScore)
{
	Super::ScoreChanged(inScore);
}

void AKAPuzzleGame::TimeLeft()
{
	Super::TimeLeft();

	for (auto& Item : CollisionObjects)
	{
		UBoxComponent* Component = Cast<UBoxComponent>(Item.Key);

		if (Component)
		{
			Component->OnComponentBeginOverlap.Clear();
		}
	}
}

void AKAPuzzleGame::GameWin()
{
	Super::GameWin();

	for (auto& Item : CollisionObjects)
	{
		UBoxComponent* Component = Cast<UBoxComponent>(Item.Key);

		if (Component)
		{
			Component->OnComponentBeginOverlap.Clear();
		}
	}
}

void AKAPuzzleGame::RestartGame()
{
	for (auto& Item : CollisionObjects)
	{
		UBoxComponent* Component = Cast<UBoxComponent>(Item.Key);

		if (Component)
		{
			Component->OnComponentBeginOverlap.Clear();
			Component->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

			UE_LOG(PuzzleGameLog, Log, TEXT("Collision Component delete - %s"), *Component->GetName());
			Component->DestroyComponent();
			Component = nullptr;
		}
		else
		{
			UE_LOG(PuzzleGameLog, Error, TEXT("Component is not valid"));
		}

		FTileData* TD = &Item.Value;

		if (TD->MI)
		{
			TD->MI = nullptr;
		}
	}

	for (auto& Item : StaticMeshObjects)
	{
		UStaticMeshComponent* Component = Cast<UStaticMeshComponent>(Item);

		if (Component)
		{
			Component->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			
			UE_LOG(PuzzleGameLog, Log, TEXT("Static mesh Component delete - %s"), *Component->GetName());
			Component->DestroyComponent();
			Component = nullptr;
		}
		else
		{
			UE_LOG(PuzzleGameLog, Error, TEXT("Component is not valid"));
		}

	}

	if (Collision)
	{
		Collision->DestroyComponent();
	}

	Collision = nullptr;
	CollisionObjects.Empty();
	StaticMeshObjects.Empty();

	countActivated = 0;
	countInnactivated = 0;

	DifficultCoefficient = ((float)CountTileX*(float)CountTileY) / 9.0f;

	CountDownTime = FTimespan::FromSeconds(FMath::TruncToInt(DifficultCoefficient*DefaultSeconds));

	bGameWin = false;

	CurrentTime = CountDownTime;
	StartTime = CountDownTime;
	
	Score = 0;

	//APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	//if (Controller->IsValidLowLevel())
	//{
	//	AKAPlayerState* PState = Cast<AKAPlayerState>(Controller->PlayerState);

	//	if (PState)
	//	{
	//		PState->Score = 0;
	//	}
	//}
	//else
	//{
	//	UE_LOG(PuzzleGameLog, Error, TEXT("Controller is not valid"));
	//}
}

void AKAPuzzleGame::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AKACharacter>(OtherActor)->IsValidLowLevel())
	{
		if (OverlappedComp)
		{
			UBoxComponent* OverlappedCollision = Cast<UBoxComponent>(OverlappedComp);

			FTileData* Data = CollisionObjects.Find(OverlappedCollision);

			Data->countSteps++;
			UE_LOG(PuzzleGameLog, Log, TEXT("CountSteps - %d"), Data->countSteps);

			if (!Data->bActivated)
			{
				Data->MI->SetVectorParameterValue(TEXT("RockTint"), ActiveColor);
				Data->bActivated = true;
				countActivated++;
				countInnactivated--;

				UGameplayStatics::PlaySoundAtLocation(GetWorld(), ActivateSound, Cast<AKACharacter>(OtherActor)->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
				
				int32 AddedScore = 50 * DifficultCoefficient / Data->countSteps;
				AddScore(AddedScore);

				UE_LOG(PuzzleGameLog, Log, TEXT("Added score - %d"), AddedScore);
			}
			else
			{
				Data->MI->SetVectorParameterValue(TEXT("RockTint"), InnactiveColor);
				Data->bActivated = false;
				countActivated--;
				countInnactivated++;

				UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeactivateSound, Cast<AKACharacter>(OtherActor)->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);

				int32 RemovedScore = 50 * DifficultCoefficient / 4 * Data->countSteps / 4;
				UE_LOG(PuzzleGameLog, Log, TEXT("Remove score - %d"), RemovedScore);

				RemoveScore(RemovedScore);
				RemoveTime(1.0f);
			}

			bGameWin = (countActivated == CollisionObjects.Num());
		}
	}
}

#if WITH_EDITOR

void AKAPuzzleGame::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UE_LOG(PuzzleGameLog, Log, TEXT("PuzzleGame OnConstruction"));

	Construct();
}

#endif

