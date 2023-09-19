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
class UDataTable;

UCLASS()
class ATOMICTHREAT_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:
	ASpawnManager();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<AGridBase> CityGrid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<AGridBase> UpperEnemyGrid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<AGridBase> RightEnemyGrid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<AGridBase> LeftEnemyGrid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Round;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataTable> DifficultyTable;

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
	float DifficultyIncrement;

	UPROPERTY()
	FTimerHandle SpawnDelayTimerHandle;

	UPROPERTY()
	float TimerValue;

	UPROPERTY()
	TArray<FRocketStruct> RocketsToSpawn;

	UPROPERTY()
	TArray<FVector> CityTargets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UFUNCTION()
	void GetRoundData();

	UFUNCTION()
	TArray<float> GetSpawnTime(int32 RocketAmount);

	UFUNCTION()
	void BeginSpawn();

	UFUNCTION()
	bool GetRandomRocketFromRoundData(TSubclassOf<ARocketBase>& RocketClass);

	UFUNCTION()
	void SpawnBasedOnGridType(AActor* Launcher, TSubclassOf<ARocketBase> Rocket, FVector Target);

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void StartRound();

	UFUNCTION()
	void SpawnGameGrids();

	UFUNCTION()
	void SetNextRound(int32 NewRound);

};
