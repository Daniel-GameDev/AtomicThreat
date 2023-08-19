// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid/LauncherBaseGridElement.h"
#include "PlayerLauncherGridElement.generated.h"

class AAtomicPawn;

UCLASS()
class ATOMICTHREAT_API APlayerLauncherGridElement : public ALauncherBaseGridElement
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AAtomicPawn> AtomicPawn;

	UFUNCTION()
	void SpawnAtomicPawn(APlayerController* PlayerController);
	
};
