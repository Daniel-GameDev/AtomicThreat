// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Common/PointsInterface.h"
#include "AtomicPlayerState.generated.h"

class AAtomicPlayerController;

UCLASS()
class ATOMICTHREAT_API AAtomicPlayerState : public APlayerState, public IPointsInterface
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<AAtomicPlayerController> CurrentPlayer;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Points;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Bonus = 1;

public:
	UFUNCTION()
	FORCEINLINE void SetBonus(int32 BonusValue) { Bonus = BonusValue; };

	// Inherited via IPointsInterface
	FORCEINLINE virtual int32 GetPoints() override { return Points; };

	FORCEINLINE virtual void SetPoints(int32 NewPoints) override { Points += NewPoints * Bonus; };

};
