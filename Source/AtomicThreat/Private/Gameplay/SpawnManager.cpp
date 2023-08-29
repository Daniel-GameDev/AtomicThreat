// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/SpawnManager.h"
#include "Grid/GridBase.h"
#include "Common/RocketStructure.h"
#include "Common/DifficultyValueStructure.h"
#include "Kismet/KismetMathLibrary.h"
#include "Gameplay/Rockets/RocketBase.h"
#include "Grid/LauncherBaseGridElement.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "Common/AtomicGameModeInterface.h"

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
		if (IAtomicGameModeInterface* Interface = Cast<IAtomicGameModeInterface>(GetWorld()->GetAuthGameMode()))
			Interface->AssignSpawnManager(this);

		TArray<FName> RowNames = DifficultyTable->GetRowNames();
		if (IAtomicGameModeInterface* Interface = Cast<IAtomicGameModeInterface>(GetWorld()->GetAuthGameMode()))
			Interface->EndGame(RowNames.Num()-1);
	}
}

void ASpawnManager::GetRoundData()
{
	TArray<FName> RowNames = DifficultyTable->GetRowNames();

	if (const FDifficultyValueStruct* DifficultyValueStruct = DifficultyTable->FindRow<FDifficultyValueStruct>(RowNames[Round], ""))
	{
		for (FRocketStruct TRocketStruct : DifficultyValueStruct->RocketTypes)
			RocketsLeft += TRocketStruct.Amount;

		SpawnTimeArray = GetSpawnTime(RocketsLeft);
		RocketsToSpawn = DifficultyValueStruct->RocketTypes;
		DifficultyIncrement = DifficultyValueStruct->DifficultyIncrement;

		if (IAtomicGameModeInterface* Interface = Cast<IAtomicGameModeInterface>(GetWorld()->GetAuthGameMode()))
			Interface->SpawnerRocketsLeft(RocketsLeft);
	}

}

TArray<float> ASpawnManager::GetSpawnTime(int32 RocketAmount)
{
	TArray<float> Time;
	
	for (size_t i = 0; i < RocketAmount; i++)
		Time.Add(UKismetMathLibrary::RandomFloatInRange(SpawnTimeMin, SpawnTimeMax));

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
				if (RocketToLaunch.GetDefaultObject()->bSideLaunch)
				{
					TArray<AActor*> LauncherArray;
					TArray<AActor*> TargetsArray;
					if (FMath::RandBool())
					{
						RightEnemyGrid->GetAttachedActors(LauncherArray);
						LeftEnemyGrid->GetAttachedActors(TargetsArray);
					}
					else
					{
						RightEnemyGrid->GetAttachedActors(TargetsArray);
						LeftEnemyGrid->GetAttachedActors(LauncherArray);
					}

					int32 RandLauncherIndex = FMath::RandRange(0, LauncherArray.Num() - 1);
					int32 RandTargetIndex = FMath::RandRange(0, TargetsArray.Num() - 1);

					SpawnBasedOnGridType(LauncherArray[RandLauncherIndex], RocketToLaunch, TargetsArray[RandTargetIndex]->GetRootComponent()->GetComponentLocation());
					bRocketSpawned = true;
					break;

				}
				else
				{
					TArray<AActor*> ElementsArray;
					UpperEnemyGrid->GetAttachedActors(ElementsArray);
					int32 RandElementIndex = FMath::RandRange(0, ElementsArray.Num() - 1);
					int32 RandTargetIndex = FMath::RandRange(0, CityTargets.Num() - 1);

					SpawnBasedOnGridType(ElementsArray[RandElementIndex], RocketToLaunch, CityTargets[RandTargetIndex]);
					bRocketSpawned = true;
					break;
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
		if (IAtomicGameModeInterface* Interface = Cast<IAtomicGameModeInterface>(GetWorld()->GetAuthGameMode()))
			Interface->SpawnerRocketsLeft(RocketsLeft);

		if (!SpawnTimeArray.IsValidIndex(0))
			GetWorldTimerManager().ClearTimer(SpawnDelayTimerHandle);
	}
	else
		TimerValue = UKismetMathLibrary::FClamp(TimerValue + SpawnerLoopFrequencyTime, SpawnTimeMin, SpawnTimeMax);
}

void ASpawnManager::SpawnBasedOnGridType(AActor* Launcher, TSubclassOf<ARocketBase> Rocket, FVector Target)
{
	if (Rocket.GetDefaultObject()->bMultiRocket)
		Cast<ALauncherBaseGridElement>(Launcher)->LaunchMultiRocket(Rocket, Target, CityTargets, DifficultyIncrement);
	else
		Cast<ALauncherBaseGridElement>(Launcher)->LaunchRocket(Rocket, FTransform(Target), DifficultyIncrement);

}

void ASpawnManager::StartRound()
{
	GetRoundData();
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
		UpperEnemyGrid->CreateBaseGird();
		RightEnemyGrid->CreateBaseGird();
		LeftEnemyGrid->CreateBaseGird();
		CityGrid->CreateBaseGird();
		TArray<AActor*> TempActors;
		CityGrid->GetAttachedActors(TempActors);
		for (AActor* TActor : TempActors)
			CityTargets.Add(TActor->GetRootComponent()->GetComponentLocation());
	}

	if (IAtomicGameModeInterface* Interface = Cast<IAtomicGameModeInterface>(GetWorld()->GetAuthGameMode()))
		Interface->AssignCityGrid(CityGrid);
}

void ASpawnManager::SetNextRound(int32 NewRound)
{
	Round = NewRound;
}

void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

