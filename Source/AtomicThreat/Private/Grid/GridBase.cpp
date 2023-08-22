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
	//TArray<AGridElementBase*> Elements;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);

	for (TSubclassOf<AGridElementBase> TGridElement : GridElementsToSpawn)
	{
		AGridElementBase* NewGridElement = GetWorld()->SpawnActor<AGridElementBase>
			(TGridElement, FVector(GetActorLocation().X, GetActorLocation().Y + Spacing, GetActorLocation().Z), GetActorRotation(), SpawnParams);
		Spacing += GridSpacing;

		NewGridElement->AttachToActor(this, TransformRules);
		//Elements.Add(NewGridElement);
	}
	
	//return Elements;
}

