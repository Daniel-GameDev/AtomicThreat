// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Rockets/RocketBase.h"
#include "MultiEnemyRocket.generated.h"

/**
 * 
 */
UCLASS()
class ATOMICTHREAT_API AMultiEnemyRocket : public ARocketBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MultiRocketSettings)
	int32 MinRocketAmount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MultiRocketSettings)
	int32 MaxRocketAmount = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MultiRocketSettings)
	TSubclassOf<ARocketBase> RocketToSpawnOnDecay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MultiRocketSettings)
	float DecayTime = 3.f;

	UPROPERTY()
	FTimerHandle DecayTimerHandle;

	UFUNCTION()
	virtual void BeginDecay();

	UFUNCTION()
	void SpawnRockets(bool bDestroyAfterSpawn);

public:
	virtual void Destroyed() override;
};