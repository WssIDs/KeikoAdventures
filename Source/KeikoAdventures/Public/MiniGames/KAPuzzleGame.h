// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KAGame.h"
#include "Sound/SoundCue.h"
#include "KAPuzzleGame.generated.h"

#define TWO_STEPS 2  // two steps on tile


class UBoxComponent;
class UStaticMeshComponent;
class UStaticMesh;

USTRUCT(BlueprintType)
struct FTileData
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
		UMaterialInstanceDynamic* MI;

	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
		bool bActivated;

	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
		int32 countSteps;
};

UCLASS()
class KEIKOADVENTURES_API AKAPuzzleGame : public AKAGame
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKAPuzzleGame();

	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite, meta = (UIMin = "3", UIMax = "15"))
		int32 CountTileX = 3;

	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite, meta = (UIMin = "3", UIMax = "15"))
		int32 CountTileY = 3;
	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
	FVector TileScale;

	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
		int32 TileOffset = 20;

	/* Использование коллизии для платформ */
	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
		bool bCollision;

	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
		FLinearColor ActiveColor;

	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
		FLinearColor InnactiveColor;

	UPROPERTY(Category = Init, VisibleAnywhere, BlueprintReadOnly)
		int32 countActivated;

	UPROPERTY(Category = Init, VisibleAnywhere, BlueprintReadOnly)
		int32 countInnactivated;

	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
		UStaticMesh* PlaneMesh;

	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
		TArray<UStaticMesh*> PlaneMeshes;

	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* PlaneMaterial;

	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
		USoundCue* ActivateSound;

	UPROPERTY(Category = Init, EditAnywhere, BlueprintReadWrite)
		USoundCue* DeactivateSound;

	UPROPERTY(Category = Init, VisibleAnyWhere)
		TArray<UStaticMeshComponent*> StaticMeshObjects;

	UPROPERTY(Category = Init, VisibleAnyWhere)
		TMap<UBoxComponent*, FTileData> CollisionObjects;

private:

	UPROPERTY()
	USceneComponent * Scene;

	UPROPERTY()
	UBoxComponent* Collision;
	
	UPROPERTY()
	int32 Distance;
	
	UPROPERTY()
	int32 DefaultSeconds;

	UFUNCTION()
	void Construct();

	UFUNCTION()
	void RestartGame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle GameTimerHandle;

public:	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Bind Overlap events and start Timer  
	//UFUNCTION(Category = Gameplay, BlueprintCallable)
		void Init();

	//UFUNCTION(Category = Gameplay, BlueprintCallable)
		void Start() override;

	// Replay game
	//UFUNCTION(Category = Gameplay, BlueprintCallable)
		void Replay() override;

	// Stop game
	//UFUNCTION(Category = Gameplay, BlueprintCallable)
		void Stop() override;

	// Create New field for Game and reset data
	UFUNCTION(Category = Init, BlueprintCallable)
		void GenerateGame(int32 countX, int32 countY, int32 offset);

	UFUNCTION(Category = Init, BlueprintCallable)
		void GenerateGameWithTeleportPlayer(int32 countX, int32 countY, int32 offset, FVector location);

	//UFUNCTION()
		void TimeLeft() override;

	//UFUNCTION()
		void GameWin() override;

	//UFUNCTION()
		void ScoreChanged(int32 inScore) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#if WITH_EDITOR

	virtual void OnConstruction(const FTransform& Transform) override;

#endif
	
};

DECLARE_LOG_CATEGORY_EXTERN(PuzzleGameLog, Log, All);
