// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ammo.generated.h"

class UArrowComponent;

UCLASS()
class ATOMICTHREAT_API AAmmo : public AActor
{
	GENERATED_BODY()
	
public:
	AAmmo();

	UFUNCTION()
	bool UseAmmo();

	UFUNCTION()
	void RefillAmmo();

	UFUNCTION()
	void ClearAmmo();

	UFUNCTION()
	int32 AmmoLeft();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> Arrow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Zero;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Even;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Odd;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 AmmoAmount = 16;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> AmmoMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TObjectPtr<UStaticMeshComponent>> Rockets;

public:
	virtual void Tick(float DeltaTime) override;

};
