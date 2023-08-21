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

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Size = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Duration = 3.f;

	UPROPERTY()
	FTimeline CurveTimeline;

	UPROPERTY(EditAnywhere, Category = Timeline)
	UCurveFloat* CurveFloat;

	UFUNCTION()
	void TraceExplosion(float ExpSize);

public:
	virtual void Tick(float DeltaTime) override;

};
