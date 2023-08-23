// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RocketBase.generated.h"

class UArrowComponent;
class UCapsuleComponent;
class UProjectileMovementComponent;
class ATargetBase;

UCLASS(Config = Game, BlueprintType)
class ATOMICTHREAT_API ARocketBase : public AActor
{
	GENERATED_BODY()
	
public:
	ARocketBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Target)
	FVector TargetVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RocketSettings)
	float DifficultyIncrement = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = RocketSettings)
	bool bSideLaunch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = RocketSettings)
	bool bMultiRocket;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RocketSettings)
	TArray<FVector> TargetVectors;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* SceneRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UArrowComponent* RocketForward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* RocketMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCapsuleComponent* RocketCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = RocketSettings)
	float InitialSpeed = 4000.f;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = RocketSettings)
	float MaxSpeed = 4000.f;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = RocketSettings)
	float RotationSpeed = 100.f;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = RocketSettings)
	float ToleranceTargetCoordinate = 400.f;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = RocketSettings)
	float HomingAccelerationMagnitude = 16000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Target)
	TSubclassOf<ATargetBase> Target;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Target)
	USceneComponent* TargetSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Debug)
	bool bDrawDebugLineRocketTrajectory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Debug)
	bool bDrawDebugLineFromStartToEnd;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Debug)
	FVector StartPoint;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Debug)
	FVector PreviousPoint;

protected:
	UFUNCTION()
	void CreateTarget();

	UFUNCTION()
	void DrawDebugLineRocketTrajectory();

	UFUNCTION()
	void DrawDebugLineFromStartToEnd();

	UFUNCTION()
	void RocketRotation(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void TargetHit();

	UFUNCTION()
	void SetProjectileSettings();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Destroyed() override;

};
