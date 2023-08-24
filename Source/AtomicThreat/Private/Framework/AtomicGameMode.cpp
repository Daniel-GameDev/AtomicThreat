// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/AtomicGameMode.h"
#include "Gameplay/SpawnManager.h"
#include "Grid/GridBase.h"
#include "Grid/GridElementBase.h"
#include "Framework/AtomicPlayerController.h"
#include "Common/PointsInterface.h"
#include "GameFramework/PlayerState.h"
#include "Framework/AtomicPlayerState.h"

void AAtomicGameMode::BeginGame()
{
	if (SpawnManager)
	{
		CityRecoveryPrice = DefaultCityRecoveryPrice;
		SpawnManager->SpawnGameGrids();
		MainPlayer->CreateUserWidget(MainPlayer->GameRoundWidget);
		StartRound();
	}
}

void AAtomicGameMode::StartRound()
{
	SpawnManager->StartRound();
}

void AAtomicGameMode::NextRound()
{
	RecoveryRandomCity();

	if (IPointsInterface* Interface = Cast<IPointsInterface>(MainPlayer->PlayerState))
		Interface->SetPoints(CityPoints + AmmoPoints);

	CityPoints = 0;
	AmmoPoints = 0;
	TotalPoints = 0;
	
	Round++;
	SpawnManager->SetNextRound(Round);

	if (Round != 1 && Round % 2 > 0)
	{
		Bonus++;
		Cast<AAtomicPlayerState>(MainPlayer->PlayerState)->SetBonus(Bonus);
	}

	StartRound();
}

void AAtomicGameMode::AssignSpawnManager(ASpawnManager* SpawnManagerRef)
{
	SpawnManager = SpawnManagerRef;
}

void AAtomicGameMode::AssignCityGrid(AGridBase* CityGridRef)
{
	CityGrid = CityGridRef;

	TArray<AActor*> CityGridActors;
	CityGrid->GetAttachedActors(CityGridActors);

	for (int32 i = 0; i < CityGridActors.Num()-1; i++)
	{
		CityGridActors[i]->OnDestroyed.AddDynamic(this, &AAtomicGameMode::OnCityElementDestroyed);

		if (Cast<AGridElementBase>(CityGridActors[i])->bRecoveryRequiresPoints)
			CityElementsLeft++;
	}
	//Actors[0]->OnDestroyed.AddDynamic(this, &AAtomicGameMode::MyDestroyed);
}

void AAtomicGameMode::OnCityElementDestroyed(AActor* DestroyedActorElement)
{
	//DestroyedElements.Add(DestroyedActorElement);
	CityElementsLeft--;

	if (CityElementsLeft == 0)
		GameLost();
}

void AAtomicGameMode::GameLost()
{
	MainPlayer->CreateUserWidget(MainPlayer->GameLostWidget);
	bGameLost = true;
}

void AAtomicGameMode::PostLogin(APlayerController* NewPlayer)
{
	MainPlayer = Cast<AAtomicPlayerController>(NewPlayer);
}

void AAtomicGameMode::RoundEnd()
{
	AGridElementBase* Element;

	int32 PointsFromPlayer;
	if (IPointsInterface* Interface = Cast<IPointsInterface>(MainPlayer->PlayerState))
		PointsFromPlayer = Interface->GetPoints();

	TArray<AActor*> CityElements;
	CityGrid->GetAttachedActors(CityElements);

	for (int32 i = 0; i < CityElements.Num(); i++)
	{
		Element = Cast<AGridElementBase>(CityElements[i]);
		if (!Element->bDestroyed)
		{
			if (Element->bRecoveryRequiresPoints)
			{
				if (IPointsInterface* Interface = Cast<IPointsInterface>(Element))
					CityPoints += Interface->GetPoints() * Bonus;
			}
			else
			{
				if (IPointsInterface* Interface = Cast<IPointsInterface>(Element))
					AmmoPoints += Interface->GetPoints() * Bonus;;
			}
		}
		/*if (!Element->bRecoveryRequiresPoints) // !!! ???
				Element->Recovery();*/
	}

	TotalPoints = CityPoints + AmmoPoints + PointsFromPlayer;

	MainPlayer->CreateUserWidget(MainPlayer->ScoreResultWidget);
}

void AAtomicGameMode::RecoveryRandomCity()
{
	AGridElementBase* Element;
	TArray<AActor*> CityElements;
	CityGrid->GetAttachedActors(CityElements);

	for (int32 i = 0; i < CityElements.Num(); i++)
	{
		Element = Cast<AGridElementBase>(CityElements[i]);
		if (!Element->bDestroyed)
		{
			if (Element->bRecoveryRequiresPoints)
				CityElements.RemoveAt(i);
			else
				Element->Recovery(); //TODO: create separate function ??
		}
		/*else if (!Element->bRecoveryRequiresPoints)
		{
			Element->Recovery();
		}*/
		/*if (!Element->bRecoveryRequiresPoints) // !!! ???
				Element->Recovery();*/
	}

	if (TotalPoints == CityRecoveryPrice)
	{
		int32 RandElement = FMath::RandRange(0, CityElements.Num() - 1);
		Cast<AGridElementBase>(CityElements[RandElement])->Recovery();
		CityRecoveryPrice += DefaultCityRecoveryPrice;
	}
}

void AAtomicGameMode::SpawnerRocketsLeft(int32 RocketsLeft)
{
	RocketsLeftInSpawner = RocketsLeft;
}

void AAtomicGameMode::TotalRocketsLeft(bool bRocketExists)
{
	if (bRocketExists)
		TotalRockets++;
	else
		TotalRockets--;

	if (TotalRockets == 0 && RocketsLeftInSpawner == 0 && bGameLost == false)
		RoundEnd();
}
