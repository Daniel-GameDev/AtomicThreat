// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridBase.generated.h"

class AGridElementBase;

UCLASS(Config = Game, BlueprintType)
class ATOMICTHREAT_API AGridBase : public AActor
{
	GENERATED_BODY()
	
public:
	AGridBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GridSettings)
	TArray<TSubclassOf<AGridElementBase>> GridElementsToSpawn;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = GridSettings)
	float GridSpacing;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void CreateBaseGird();

};
