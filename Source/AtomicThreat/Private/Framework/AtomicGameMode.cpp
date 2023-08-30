// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/AtomicGameMode.h"
#include "Gameplay/SpawnManager.h"
#include "Grid/GridBase.h"
#include "Grid/GridElementBase.h"
#include "Framework/AtomicPlayerController.h"
#include "Common/PointsInterface.h"
#include "Framework/AtomicPlayerState.h"

void AAtomicGameMode::BeginGame()
{
	if (SpawnManager)
	{
		CityRecoveryPrice = DefaultCityRecoveryPrice;
		SpawnManager->SpawnGameGrids();
		MainPlayer->CreateUserWidget(MainPlayer->GameRoundWidget);
		SpawnManager->SetNextRound(Round);
		SpawnManager->StartRound();
	}
}

void AAtomicGameMode::NextRound()
{
	CityRecovery();

	if (IPointsInterface* Interface = Cast<IPointsInterface>(MainPlayer->PlayerState))
		Interface->SetPoints(CityPoints / Bonus + AmmoPoints / Bonus);

	CityPoints = AmmoPoints = TotalPoints = 0;
	
	Round++;
	SpawnManager->SetNextRound(Round);

	if (Round != 1 && Round % 2 == 0)
	{
		Bonus++;
		Cast<AAtomicPlayerState>(MainPlayer->PlayerState)->SetBonus(Bonus);
	}

	SpawnManager->StartRound();
}

void AAtomicGameMode::SetSpawnManager(ASpawnManager* SpawnManagerRef)
{
	SpawnManager = SpawnManagerRef;
}

void AAtomicGameMode::AssignCityGrid(AGridBase* CityGridRef)
{
	CityGrid = CityGridRef;
	TArray<AActor*> CityGridActors;
	CityGrid->GetAttachedActors(CityGridActors);

	for (int32 i = 0; i < CityGridActors.Num(); i++)
	{
		CityGridActors[i]->OnDestroyed.AddDynamic(this, &AAtomicGameMode::OnCityElementDestroyed);

		if (Cast<AGridElementBase>(CityGridActors[i])->bRecoveryRequiresPoints)
			CityElementsLeft++;
	}
}

void AAtomicGameMode::OnCityElementDestroyed(AActor* DestroyedActorElement)
{
	if (Cast<AGridElementBase>(DestroyedActorElement)->bRecoveryRequiresPoints)
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
	int32 PointsFromPlayer;
	AGridElementBase* Element;
	TArray<AActor*> CityElements;

	if (IPointsInterface* Interface = Cast<IPointsInterface>(MainPlayer->PlayerState))
		PointsFromPlayer = Interface->GetPoints();

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
	}

	TotalPoints = CityPoints + AmmoPoints + PointsFromPlayer;

	if (Round == LastRound)
		MainPlayer->CreateUserWidget(MainPlayer->EndGameWidget);
	else
		MainPlayer->CreateUserWidget(MainPlayer->ScoreResultWidget);
}

void AAtomicGameMode::CityRecovery()
{
	AGridElementBase* Element;
	TArray<AActor*> CityElements;
	TArray<AGridElementBase*> DestroyedElements;
	CityGrid->GetAttachedActors(CityElements);
	int32 ArrayLenght = CityElements.Num();

	for (int32 i = 0; i < CityElements.Num(); i++)
	{
		Element = Cast<AGridElementBase>(CityElements[i]);
		if (Element->bRecoveryRequiresPoints && Element->bDestroyed)
			DestroyedElements.Add(Element);
		else if (!Element->bRecoveryRequiresPoints)
			Element->Recovery();
	}
	
	if (TotalPoints >= CityRecoveryPrice && DestroyedElements.IsValidIndex(0))
	{
		int32 RandElement = FMath::RandRange(0, DestroyedElements.Num() - 1);
		DestroyedElements[RandElement]->Recovery();
		CityRecoveryPrice += DefaultCityRecoveryPrice;
		CityElementsLeft++;
	}
}

void AAtomicGameMode::SetRocketsLeft(int32 RocketsLeft)
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

void AAtomicGameMode::EndGame(int32 TotalRounds)
{
	LastRound = TotalRounds;
}

void AAtomicGameMode::StartPlayerCameraShake()
{
	MainPlayer->StartCameraShake();
}
