// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid/GridElementBase.h"
#include "LauncherBaseGridElement.generated.h"

class ARocketBase;

UCLASS()
class ATOMICTHREAT_API ALauncherBaseGridElement : public AGridElementBase
{
	GENERATED_BODY()

public:
	ALauncherBaseGridElement();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* RocketLauncherMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* LaunchPoint;

public:
	UFUNCTION(BlueprintCallable)
	void LaunchRocket(TSubclassOf<ARocketBase> RocketType, FVector TargetVector, float DifficultyIncrement);

};
