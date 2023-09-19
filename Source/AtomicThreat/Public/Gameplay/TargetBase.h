// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetBase.generated.h"

UCLASS()
class ATOMICTHREAT_API ATargetBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATargetBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> SceneRoot;

public:	
	virtual void Tick(float DeltaTime) override;

};
