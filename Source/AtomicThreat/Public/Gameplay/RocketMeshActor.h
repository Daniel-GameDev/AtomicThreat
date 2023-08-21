// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RocketMeshActor.generated.h"

UCLASS()
class ATOMICTHREAT_API ARocketMeshActor : public AActor // < delete
{
	GENERATED_BODY()

public:
	ARocketMeshActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* RocketMesh;

protected:
	virtual void BeginPlay() override;

};