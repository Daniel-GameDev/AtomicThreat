// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Rockets/RocketBase.h"
#include "Common/PointsInterface.h"
#include "EnemyRocket.generated.h"

UCLASS()
class ATOMICTHREAT_API AEnemyRocket : public ARocketBase, public IPointsInterface
{
	GENERATED_BODY()

public:
	AEnemyRocket();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Points;

public:
	// Inherited via IPointsInterface
	FORCEINLINE virtual int32 GetPoints() override { return Points; };

	FORCEINLINE virtual void SetPoints(int32 NewPoints) override {}

};
