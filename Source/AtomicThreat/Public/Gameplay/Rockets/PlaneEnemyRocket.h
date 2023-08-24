// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Rockets/MultiEnemyRocket.h"
//#include "Common/PointsInterface.h"
#include "PlaneEnemyRocket.generated.h"

/**
 * 
 */
UCLASS()
class ATOMICTHREAT_API APlaneEnemyRocket : public AMultiEnemyRocket
{
	GENERATED_BODY()
	
public: 
	APlaneEnemyRocket();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* AttachedRocketMesh;

	virtual void BeginDecay() override;

/*protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Points;*/

public:
	// Inherited via IPointsInterface
	virtual int32 GetPoints() override;
	virtual void SetPoints(int32 NewPoints) override;
};
