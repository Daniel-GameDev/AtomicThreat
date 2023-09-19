// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AtomicGameMode.generated.h"

class ASpawnManager;
class AGridBase;
class AAtomicPlayerController;

UCLASS()
class ATOMICTHREAT_API AAtomicGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	int32 Round;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 AmmoPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CityPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TotalPoints;

	UFUNCTION(BlueprintCallable)
	void BeginGame();

	UFUNCTION(BlueprintCallable)
	void NextRound();

	UFUNCTION()
	void SetSpawnManager(ASpawnManager* SpawnManagerRef);

	UFUNCTION()
	void AssignCityGrid(AGridBase* CityGridRef);

	UFUNCTION()
	void SetRocketsLeft(int32 RocketLeft);

	UFUNCTION()
	void TotalRocketsLeft(bool bRocketExists);

	UFUNCTION()
	void EndGame(int32 TotalRounds);

	UFUNCTION()
	void StartPlayerCameraShake();

protected:
	UPROPERTY()
	TObjectPtr<AAtomicPlayerController> MainPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ASpawnManager> SpawnManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AGridBase> CityGrid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 DefaultCityRecoveryPrice = 10000;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CityRecoveryPrice;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 RocketsLeftInSpawner;

	UPROPERTY()
	int32 CityElementsLeft;

	UPROPERTY()
	int32 TotalRockets;

	UPROPERTY()
	bool bGameLost;

	UPROPERTY()
	int32 LastRound;

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
