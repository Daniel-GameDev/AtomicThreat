// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/GridElementBase.h"

AGridElementBase::AGridElementBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("GridSceneRoot"));
	SetRootComponent(SceneRoot);

	GridMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridBaseMesh"));
	GridMesh->SetupAttachment(SceneRoot);
}

void AGridElementBase::BeginPlay()
{
	Super::BeginPlay();
}

void AGridElementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

