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
	APlayerController* PlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector ExplosionCoordinate;

	UFUNCTION()
	void TimelineProgress(float Value);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Size;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Duration;

	UPROPERTY()
	FTimeline CurveTimeline;

	UPROPERTY(EditAnywhere, Category = Timeline)
	UCurveFloat* CurveFloat;

	/*UPROPERTY()
	FVector StartLoc;

	UPROPERTY()
	FVector EndLoc;*/

	UPROPERTY(EditAnywhere, Category = Timeline)
	float ZOffset;

	UFUNCTION()
	void TraceExplosion(float ExpSize);

public:
	virtual void Tick(float DeltaTime) override;

};
