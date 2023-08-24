// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AtomicGameModeInterface.generated.h"

class ASpawnManager;
class AGridBase;

UINTERFACE(MinimalAPI)
class UAtomicGameModeInterface : public UInterface
{
	GENERATED_BODY()
};

class ATOMICTHREAT_API IAtomicGameModeInterface
{
	GENERATED_BODY()

public:

	/*UFUNCTION()
	virtual void AssignGameElements(ASpawnManager* SpawnManagerRef, AGridBase* CityGridRef) = 0;*/

	UFUNCTION()
	virtual void AssignSpawnManager(ASpawnManager* SpawnManagerRef) = 0;

	UFUNCTION()
	virtual void AssignCityGrid(AGridBase* CityGridRef) = 0;

	UFUNCTION()
	virtual void SpawnerRocketsLeft(int32 RocketsLeft) = 0;

	UFUNCTION()
	virtual void TotalRocketsLeft(bool bRocketExists) = 0;
};
