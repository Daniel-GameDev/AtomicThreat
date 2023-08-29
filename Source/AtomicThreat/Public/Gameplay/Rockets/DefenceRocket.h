// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Rockets/RocketBase.h"
#include "DefenceRocket.generated.h"

class ADefenceExplosion;

UCLASS()
class ATOMICTHREAT_API ADefenceRocket : public ARocketBase
{
	GENERATED_BODY()
public:
	ADefenceRocket();

	virtual void Destroyed() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ADefenceExplosion> Explosion;

	UFUNCTION()
	void SpawnExplosion();
};
