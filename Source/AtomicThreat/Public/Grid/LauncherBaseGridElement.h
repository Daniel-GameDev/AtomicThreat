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
	TObjectPtr<UStaticMeshComponent> RocketLauncherMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> LaunchPoint;

public:
	UFUNCTION(BlueprintCallable)
	virtual void LaunchRocket(TSubclassOf<ARocketBase> RocketType, FTransform TargetTransform, float DifficultyIncrement, APlayerController* PlayerController = nullptr);

	UFUNCTION(BlueprintCallable)
	virtual void LaunchMultiRocket(TSubclassOf<ARocketBase> RocketType, FVector TargetVector, TArray<FVector> TargetVectors, float DifficultyIncrement);

};
