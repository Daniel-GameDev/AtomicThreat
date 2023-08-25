// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Common/AtomicGameModeInterface.h"
#include "AtomicGameMode.generated.h"

class ASpawnManager;
class AGridBase;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 AmmoPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CityPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TotalPoints;

	UFUNCTION(BlueprintCallable)
	void BeginGame();

	UFUNCTION(BlueprintCallable)
	void StartRound();

	UFUNCTION(BlueprintCallable)
	void NextRound();

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 DefaultCityRecoveryPrice = 10000;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CityRecoveryPrice;

	UPROPERTY()
	int32 CityElementsLeft;

	UPROPERTY()
	int32 TotalRockets;

	UPROPERTY()
	bool bGameLost;

	UPROPERTY()
	int32 Bonus = 1;

	UFUNCTION()
	void OnCityElementDestroyed(AActor* Act);

	UFUNCTION()
	void GameLost();

	UFUNCTION()
	void RoundEnd();

	UFUNCTION()
	void CityRecovery();

	virtual void PostLogin(APlayerController* NewPlayer) override;

};
