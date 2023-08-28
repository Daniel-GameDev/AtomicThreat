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
	float Spacing = 0.f;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
	FVector ActorLocation;

	for (TSubclassOf<AGridElementBase> TGridElement : GridElementsToSpawn)
	{
		if (TGridElement)
		{
			AGridElementBase* NewGridElement = GetWorld()->SpawnActor<AGridElementBase>(TGridElement, FVector(ActorLocation.X, ActorLocation.Y + Spacing, ActorLocation.Z), GetActorRotation(), SpawnParams);
			Spacing = GridSpacing;

			ActorLocation = NewGridElement->GetActorLocation();
			NewGridElement->AttachToActor(this, TransformRules);
		}
	}
}

