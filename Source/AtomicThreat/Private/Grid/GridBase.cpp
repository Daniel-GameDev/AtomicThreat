// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/GridBase.h"
#include "Grid/GridElementBase.h"

AGridBase::AGridBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGridBase::BeginPlay()
{
	Super::BeginPlay();
}

void AGridBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGridBase::CreateBaseGird()
{
	FVector SpawnLocation = FVector(0);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);

	for (TSubclassOf<AGridElementBase> TGridElement : GridElementsToSpawn)
	{
		if (TGridElement)
		{
			AGridElementBase* NewGridElement = GetWorld()->SpawnActor<AGridElementBase>(TGridElement, SpawnLocation, GetActorRotation(), SpawnParams);
			SpawnLocation = FVector(0, SpawnLocation.Y + GridSpacingY, SpawnLocation.Z - GridSpacingZ);
			NewGridElement->AttachToActor(this, TransformRules);
		}
	}
}

