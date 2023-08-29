// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/TargetBase.h"
#include "PlayerTarget.generated.h"

/**
 * 
 */
UCLASS()
class ATOMICTHREAT_API APlayerTarget : public ATargetBase
{
	GENERATED_BODY()
	
public:
	APlayerTarget();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* MeshScene;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* TargetMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RollValue = 200.f;

	UFUNCTION()
	void RotateTarget(float Tick);

public:
	virtual void Tick(float DeltaTime) override;
};
