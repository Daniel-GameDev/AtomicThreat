// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Rockets/MultiEnemyRocket.h"
#include "Kismet/GameplayStatics.h"

void AMultiEnemyRocket::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(DecayTimerHandle, this, &AMultiEnemyRocket::BeginDecay, DecayTime, false);
}

int32 AMultiEnemyRocket::GetPoints()
{
	return Points;
}

void AMultiEnemyRocket::BeginDecay()
{
	SpawnRockets(true);
}

void AMultiEnemyRocket::SpawnRockets(bool bDestroyAfterSpawn)
{
	if (GetWorld() && RocketToSpawnOnDecay)
	{
		int32 RandRocketAmount = FMath::RandRange(MinRocketAmount, MaxRocketAmount);
		TArray<FVector> Targets = TargetVectors;
		for (int32 i = 0; i < RandRocketAmount; i++)
		{
			AActor* RocketActor = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), RocketToSpawnOnDecay, FTransform(GetActorLocation()), ESpawnActorCollisionHandlingMethod::Undefined, nullptr);
			if (ARocketBase* RocketBase = Cast<ARocketBase>(RocketActor))
			{
				int32 RandTargetIndex = FMath::RandRange(0, TargetVectors.Num() - 1);
				RocketBase->TargetTransform.SetLocation(TargetVectors[RandTargetIndex]);// = ;
				RocketBase->DifficultyIncrement = DifficultyIncrement;
				if (RocketBase->bMultiRocket)
				{
					RocketBase->TargetVectors = Targets;
				}
				TargetVectors.RemoveAt(RandTargetIndex);
			}

			UGameplayStatics::FinishSpawningActor(RocketActor, FTransform(GetActorLocation()));
		}
		if (bDestroyAfterSpawn)
			Destroy();
		
	}
}

void AMultiEnemyRocket::Destroyed()
{
	GetWorldTimerManager().ClearTimer(DecayTimerHandle);

	Super::Destroyed();
}
