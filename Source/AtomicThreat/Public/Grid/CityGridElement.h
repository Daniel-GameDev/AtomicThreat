// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid/GridElementBase.h"
#include "CityGridElement.generated.h"

class UCapsuleComponent;

UCLASS()
class ATOMICTHREAT_API ACityGridElement : public AGridElementBase
{
	GENERATED_BODY()

public:
	ACityGridElement();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* DefaultCityMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* DestroyedCityMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCapsuleComponent* CityCapsule;

public:
	UFUNCTION(BlueprintCallable)
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	void RestoreCity();

	virtual void Destroyed() override;
};
