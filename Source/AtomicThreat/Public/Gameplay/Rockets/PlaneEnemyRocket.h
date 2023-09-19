// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Rockets/MultiEnemyRocket.h"
#include "PlaneEnemyRocket.generated.h"

UCLASS()
class ATOMICTHREAT_API APlaneEnemyRocket : public AMultiEnemyRocket
{
	GENERATED_BODY()
	
public: 
	APlaneEnemyRocket();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> AttachedRocketMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> SecondNiagaraComponent;

	virtual void BeginDecay() override;

	virtual void TargetHit() override;

public:
	// Inherited via IPointsInterface
	FORCEINLINE virtual int32 GetPoints() override { return Points; };

	FORCEINLINE virtual void SetPoints(int32 NewPoints) override {};
};
