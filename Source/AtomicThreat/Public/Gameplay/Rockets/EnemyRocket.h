// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Rockets/RocketBase.h"
#include "EnemyRocket.generated.h"

/**
 * 
 */
UCLASS()
class ATOMICTHREAT_API AEnemyRocket : public ARocketBase
{
	GENERATED_BODY()

public:
	AEnemyRocket();

	UFUNCTION()
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	
};
