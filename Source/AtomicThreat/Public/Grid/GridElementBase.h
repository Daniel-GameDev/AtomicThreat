// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridElementBase.generated.h"

UCLASS()
class ATOMICTHREAT_API AGridElementBase : public AActor
{
	GENERATED_BODY()
	
public:
	AGridElementBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bDestroyed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Points;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bRecoveryRequiresPoints;

	UFUNCTION()
	virtual void Recovery() PURE_VIRTUAL(AGridElementBase::Recovery, );

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> GridMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UParticleSystemComponent> DestroyedParticle;

public:
	virtual void Tick(float DeltaTime) override;

};
