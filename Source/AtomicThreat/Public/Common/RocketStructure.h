// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Gameplay/Rockets/RocketBase.h"
#include "RocketStructure.generated.h"

class ARocketBase;

USTRUCT(BlueprintType)
struct FRocketStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARocketBase> RocketType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount;
};
