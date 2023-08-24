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
		// Inherited via IPointsInterface
	virtual int32 GetPoints() override;

	virtual void SetPoints(int32 NewPoints) override;

	UPROPERTY()
	AAtomicPlayerController* CurrentPlayer;

	UFUNCTION()
	void SetBonus(int32 BonusValue);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Points;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Bonus = 1;
	

	

};
