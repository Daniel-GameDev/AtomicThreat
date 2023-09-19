// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "DefenceExplosion.generated.h"

UCLASS()
class ATOMICTHREAT_API ADefenceExplosion : public AActor
{
	GENERATED_BODY()
	
public:
	ADefenceExplosion();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector ExplosionCoordinate;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Size = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Duration = 3.f;

	UPROPERTY(EditAnywhere, Category = Timeline)
	TObjectPtr<UCurveFloat> CurveFloat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UParticleSystem> ExplosionParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SizeDevider = 100.f;

	UPROPERTY()
	FTimeline CurveTimeline;

	UFUNCTION()
	void TraceExplosion(float ExpSize);

	UFUNCTION()
	void TraceExplosionFinished();

public:
	virtual void Tick(float DeltaTime) override;

};
