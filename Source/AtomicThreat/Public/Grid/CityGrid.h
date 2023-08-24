// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid/GridBase.h"
#include "CityGrid.generated.h"

/**
 * 
 */
UCLASS()
class ATOMICTHREAT_API ACityGrid : public AGridBase // Delete
{
	GENERATED_BODY()
	
public:
	virtual void CreateBaseGird() override;

protected:
	UPROPERTY()
	TArray<int32> PointsElementsIndex;
};
