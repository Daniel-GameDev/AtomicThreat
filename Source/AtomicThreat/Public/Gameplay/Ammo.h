// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ammo.generated.h"

class UArrowComponent;
class ARocketMeshActor; // < delete

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
	USceneComponent* SceneRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UArrowComponent* Arrow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* Zero;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* Even;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* Odd;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 AmmoAmount = 16;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMesh* AmmoMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<UStaticMeshComponent*> Rockets;

public:
	virtual void Tick(float DeltaTime) override;

/*private:
	UPROPERTY()
	int32 AmmoLeft;*/

};
