// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/RocketStructure.h"
#include "Engine/DataTable.h"
#include "DifficultyValueStructure.generated.h"

USTRUCT(BlueprintType)
struct FDifficultyValueStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DifficultyIncrement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRocketStruct> RocketTypes;

};