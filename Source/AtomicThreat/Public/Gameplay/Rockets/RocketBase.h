// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RocketBase.generated.h"

class UArrowComponent;
class UCapsuleComponent;
class UProjectileMovementComponent;
class ATargetBase;
class UNiagaraComponent;

UCLASS(Config = Game, BlueprintType)
class ATOMICTHREAT_API ARocketBase : public AActor
{
	GENERATED_BODY()
	
public:
	ARocketBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Target)
	FTransform TargetTransform;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RocketSettings)
	float DifficultyIncrement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = RocketSettings)
	bool bSideLaunch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = RocketSettings)
	bool bMultiRocket;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RocketSettings)
	TArray<FVector> TargetVectors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APlayerController* PlayerController;

	UFUNCTION()
	void SetProjectileSettings();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* SceneRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UArrowComponent* RocketForward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* RocketMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* RocketSkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCapsuleComponent* RocketCapsule;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UNiagaraComponent* NiagaraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = RocketSettings)
	float InitialSpeed;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = RocketSettings)
	float MaxSpeed;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = RocketSettings)
	float RotationSpeed;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = RocketSettings)
	float ToleranceTargetCoordinate;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = RocketSettings)
	float HomingAccelerationMagnitude;

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

	

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Destroyed() override;

};
