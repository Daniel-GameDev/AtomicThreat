// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Common/AtomicGameModeInterface.h" //<<< Delete?
#include "AtomicGameMode.generated.h"

class ASpawnManager;
class AGridBase;
class AGridElementBase;
class AAtomicPlayerController;

UCLASS()
class ATOMICTHREAT_API AAtomicGameMode : public AGameModeBase, public IAtomicGameModeInterface
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Round;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 RocketsLeftInSpawner;

	UFUNCTION(BlueprintCallable)
	void BeginGame();

	UFUNCTION(BlueprintCallable)
	void StartRound();

	UFUNCTION()
	virtual void AssignSpawnManager(ASpawnManager* SpawnManagerRef) override;

	UFUNCTION()
	virtual void AssignCityGrid(AGridBase* CityGridRef) override;

	UFUNCTION()
	virtual void SpawnerRocketsLeft(int32 RocketLeft) override;

	UFUNCTION()
	virtual void TotalRocketsLeft(bool bRocketExists) override;

protected:
	UPROPERTY()
	AAtomicPlayerController* MainPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ASpawnManager* SpawnManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AGridBase* CityGrid;

	UPROPERTY()
	TArray<AGridElementBase*> DestroyedElements;

	UPROPERTY()
	int32 CityElementsLeft;

	UPROPERTY()
	int32 TotalRockets;

	UFUNCTION()
	void OnCityElementDestroyed(AActor* Act);

	UFUNCTION()
	void GameLost(); //TODO: add game lost to player controller

	virtual void PostLogin(APlayerController* NewPlayer) override;

};
