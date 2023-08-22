// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/SpawnManager.h"
#include "Grid/GridBase.h"
#include "Common/RocketStructure.h"
#include "Common/DifficultyValueStructure.h"
#include "Kismet/KismetMathLibrary.h"
#include "Gameplay/Rockets/RocketBase.h"

ASpawnManager::ASpawnManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		CityGrid->CreateBaseGird();
		UpperEnemyGrid->CreateBaseGird();
		RightEnemyGrid->CreateBaseGird();
		LeftEnemyGrid->CreateBaseGird();
	}
}

void ASpawnManager::GetRoundData()
{
	TArray<FName> RowNames = DifficultyTable->GetRowNames();
	FDifficultyValueStruct* DifficultyValueStruct = DifficultyTable->FindRow<FDifficultyValueStruct>(RowNames[Round], "");

	for (FRocketStruct TRocketStruct : DifficultyValueStruct->RocketTypes)
		RocketAmount += TRocketStruct.Amount;

	SpawnTimeArray = GetSpawnTime(RocketAmount);
	RocketsToSpawn = DifficultyValueStruct->RocketTypes;
}

TArray<float> ASpawnManager::GetSpawnTime(int32 RocketAmount)
{
	TArray<float> Time;

	for (size_t i = 0; i < RocketAmount; i++)
	{
		Time.Add(UKismetMathLibrary::RandomFloatInRange(SpawnTimeMin, SpawnTimeMax));
	}

	return Time;
}

void ASpawnManager::BeginSpawn()
{
	bool bRocketSpawned = false;
	TSubclassOf<ARocketBase>* RocketToLaunch;

	for (float TTime : SpawnTimeArray)
	{
		if (TTime <= TimerValue)
		{
			SpawnTimeArray.RemoveSingle(TTime);
			if (GetRandomRocketFromRoundData(RocketToLaunch))
			{
				
			}
			else
			{
				GetWorldTimerManager().ClearTimer(SpawnDelayTimerHandle);
				break;
			}
		}
	}

	if (bRocketSpawned)
	{
		RocketAmount--;
		if (SpawnTimeArray.IsValidIndex(0))
			GetWorldTimerManager().ClearTimer(SpawnDelayTimerHandle);
	}
	else
	{
		TimerValue = UKismetMathLibrary::FClamp(TimerValue + SpawnerLoopFrequencyTime, SpawnTimeMax, SpawnTimeMin);
		//bRocketSpawned = false;
	}
}

void ASpawnManager::StartRound()
{
	GetRoundData();
	GetWorld()->GetTimerManager().SetTimer(SpawnDelayTimerHandle, this, &ASpawnManager::BeginSpawn, SpawnerLoopFrequencyTime, true);
}

bool ASpawnManager::GetRandomRocketFromRoundData(TSubclassOf<ARocketBase>* RocketClass)
{
	RocketsToSpawn

	return false;
}

void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

