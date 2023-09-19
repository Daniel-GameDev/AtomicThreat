// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid/GridElementBase.h"
#include "Common/PointsInterface.h"
#include "CityGridElement.generated.h"

class UCapsuleComponent;

UCLASS()
class ATOMICTHREAT_API ACityGridElement : public AGridElementBase, public IPointsInterface
{
	GENERATED_BODY()

public:
	ACityGridElement();

	virtual void Recovery() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> DefaultCityMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> DestroyedCityMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> CityCapsule;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UParticleSystem> ExplosionParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ExplosionScale = 3.f;

public:
	UFUNCTION(BlueprintCallable)
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	void RestoreCity();

	virtual void Destroyed() override;

	// Inherited via IPointsInterface
	FORCEINLINE virtual int32 GetPoints() override { return Points; }

	FORCEINLINE virtual void SetPoints(int32 NewPoints) override {}
	
};
