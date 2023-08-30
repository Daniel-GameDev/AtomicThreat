// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PointsInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPointsInterface : public UInterface
{
	GENERATED_BODY()
};

class ATOMICTHREAT_API IPointsInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual int32 GetPoints() = 0;

	UFUNCTION()
	virtual void SetPoints(int32 NewPoints) = 0;

};
