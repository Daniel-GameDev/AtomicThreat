// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/SpawnManager.h"
#include "Grid/GridBase.h"
#include "Common/RocketStructure.h"
#include "Common/DifficultyValueStructure.h"
#include "Kismet/KismetMathLibrary.h"
#include "Gameplay/Rockets/RocketBase.h"
//#include "Kismet/KismetArrayLibrary.h"
#include "Grid/LauncherBaseGridElement.h"

ASpawnManager::ASpawnManager()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);
}

void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		SpawnGameGrids();

		if (true)
		{
			StartRound();
		}
	}
}

void ASpawnManager::GetRoundData()
{
	TArray<FName> RowNames = DifficultyTable->GetRowNames();
	FDifficultyValueStruct* DifficultyValueStruct = DifficultyTable->FindRow<FDifficultyValueStruct>(RowNames[Round], "");

	for (FRocketStruct TRocketStruct : DifficultyValueStruct->RocketTypes)
		RocketsLeft += TRocketStruct.Amount;

	SpawnTimeArray = GetSpawnTime(RocketsLeft);
	RocketsToSpawn = DifficultyValueStruct->RocketTypes;
	DifficultyIncrement = DifficultyValueStruct->DifficultyIncrement;
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
	TSubclassOf<ARocketBase> RocketToLaunch;

	for (float TTime : SpawnTimeArray)
	{
		if (TTime <= TimerValue)
		{
			SpawnTimeArray.RemoveSingle(TTime);
			if (GetRandomRocketFromRoundData(RocketToLaunch))
			{
				//TSubclassOf<ARocketBase> Rocket = RocketToLaunch;
				//Rocket.GetDefaultObject()->bSideLaunch;
				if (RocketToLaunch.GetDefaultObject()->bSideLaunch)
				{
					//TODO: Side Launch
				}
				else
				{
					TArray<AActor*> ElementsArray;
					UpperEnemyGrid->GetAttachedActors(ElementsArray);
					int32 RandElementIndex = FMath::RandRange(0, ElementsArray.Num() - 1);
					int32 RandTargetIndex = FMath::RandRange(0, CityTargets.Num() - 1);
					//ElementsArray[RandElementIndex];

					Cast<ALauncherBaseGridElement>(ElementsArray[RandElementIndex])->LaunchRocket(RocketToLaunch, CityTargets[RandTargetIndex], DifficultyIncrement);
					bRocketSpawned = true;
				}
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
		RocketsLeft--;
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
	//GetWorld()->GetTimerManager().SetTimer(SpawnDelayTimerHandle,  &ASpawnManager::BeginSpawn, SpawnerLoopFrequencyTime, true);
	GetWorld()->GetTimerManager().SetTimer(SpawnDelayTimerHandle, this, &ASpawnManager::BeginSpawn, SpawnerLoopFrequencyTime, true);
}

bool ASpawnManager::GetRandomRocketFromRoundData(TSubclassOf<ARocketBase>& RocketClass)
{
	if (RocketsToSpawn.IsValidIndex(0))
	{
		int32 RandIndex = FMath::RandRange(0, RocketsToSpawn.Num() - 1);
		RocketClass = RocketsToSpawn[RandIndex].RocketType;
		RocketsToSpawn[RandIndex].Amount--;

		if (RocketsToSpawn[RandIndex].Amount == 0)
			RocketsToSpawn.RemoveAt(RandIndex);
			
	}
	else return false;
	

	return true;
}

void ASpawnManager::SpawnGameGrids()
{
	if (CityGrid && UpperEnemyGrid && RightEnemyGrid && LeftEnemyGrid)
	{
		CityGrid->CreateBaseGird();
		TArray<AActor*> TempActors;
		CityGrid->GetAttachedActors(TempActors);
		for (AActor* TActor : TempActors)
			CityTargets.Add(TActor->GetRootComponent()->GetComponentLocation());

		UpperEnemyGrid->CreateBaseGird();
		RightEnemyGrid->CreateBaseGird();
		LeftEnemyGrid->CreateBaseGird();
	}
}

void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

