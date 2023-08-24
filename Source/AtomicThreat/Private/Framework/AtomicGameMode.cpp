// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/AtomicGameMode.h"
#include "Gameplay/SpawnManager.h"
#include "Grid/GridBase.h"
#include "Grid/GridElementBase.h"
#include "Framework/AtomicPlayerController.h"

void AAtomicGameMode::BeginGame()
{
	if (SpawnManager)
	{
		SpawnManager->SpawnGameGrids();
		MainPlayer->CreateUserWidget(MainPlayer->GameRoundWidget);
		StartRound();
	}
}

void AAtomicGameMode::StartRound()
{
	SpawnManager->StartRound();
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
	DestroyedElements.Add(Cast<AGridElementBase>(DestroyedActorElement));
	CityElementsLeft--;

	if (CityElementsLeft == 0)
		GameLost();
}

void AAtomicGameMode::GameLost() //TODO: GameLost
{
	MainPlayer->CreateUserWidget(MainPlayer->GameLostWidget);
}

void AAtomicGameMode::PostLogin(APlayerController* NewPlayer)
{
	MainPlayer = Cast<AAtomicPlayerController>(NewPlayer);
}
