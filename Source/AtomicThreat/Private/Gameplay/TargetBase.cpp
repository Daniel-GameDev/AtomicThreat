// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TargetBase.h"

ATargetBase::ATargetBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
}

void ATargetBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATargetBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

