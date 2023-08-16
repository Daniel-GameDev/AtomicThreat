// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridBase.generated.h"

class AGridElementBase;

USTRUCT(BlueprintType)
struct FGridElementState
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TSubclassOf<AGridElementBase> OnCreate;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TSubclassOf<AGridElementBase> OnDestroy;
};

UCLASS(Config=Game, BlueprintType)
class ATOMICTHREAT_API AGridBase : public AActor
{
	GENERATED_BODY()
	
public:
	AGridBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<struct FGridElementState> GridElementsToSpawn;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = GridSettings)
	bool bShowDebugGrid;

public:
	virtual void Tick(float DeltaTime) override;

};
