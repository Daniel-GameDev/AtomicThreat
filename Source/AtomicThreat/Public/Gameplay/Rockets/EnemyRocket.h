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

	UFUNCTION()
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	

	// Inherited via IPointsInterface
	virtual int32 GetPoints() override;

	FORCEINLINE virtual void SetPoints(int32 NewPoints) override {}

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Points;

};
