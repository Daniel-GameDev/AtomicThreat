// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Common/RocketStructure.h"
#include "Common/DifficultyValueStructure.h"
#include "SpawnManager.generated.h"

class AGridBase;
class AGridElementBase;
class ARocketBase;
//class FRocketStruct;
class UDataTable;

/*USTRUCT(BlueprintType)
struct FDifficultyData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TotalRockets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DifficultyIncrement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRocketStruct> RocketsToSpawn;

};*/

UCLASS()
class ATOMICTHREAT_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:
	ASpawnManager();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AGridBase* CityGrid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AGridBase* UpperEnemyGrid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AGridBase* RightEnemyGrid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AGridBase* LeftEnemyGrid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Round;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* DifficultyTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Spawner)
	float SpawnTimeMax = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Spawner)
	float SpawnTimeMin = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Spawner)
	float SpawnerLoopFrequencyTime = 0.5f;

	UPROPERTY()
	TArray<float> SpawnTimeArray;

	UPROPERTY()
	int32 RocketsLeft;

	UPROPERTY()
	int32 DifficultyIncrement;

	UPROPERTY()
	FTimerHandle SpawnDelayTimerHandle;

	UPROPERTY()
	float TimerValue;

	UPROPERTY()
	TArray<FRocketStruct> RocketsToSpawn;

	UPROPERTY()
	TArray<FVector> CityTargets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	UFUNCTION()
	void GetRoundData();

	UFUNCTION()
	TArray<float> GetSpawnTime(int32 RocketAmount);

	UFUNCTION()
	void BeginSpawn();

	UFUNCTION()
	void StartRound();

	UFUNCTION()
	bool GetRandomRocketFromRoundData(TSubclassOf<ARocketBase>& RocketClass);

	UFUNCTION()
	void SpawnGameGrids();

public:
	virtual void Tick(float DeltaTime) override;
	
	/*UPROPERTY() // <<< already have linkl on all attached components
	TArray<AGridElementBase*> UpperEnemyGridElements;

	UPROPERTY()
	TArray<AGridElementBase*> RightEnemyGridElements;

	UPROPERTY()
	TArray<AGridElementBase*> LeftEnemyGridElements;*/

};
