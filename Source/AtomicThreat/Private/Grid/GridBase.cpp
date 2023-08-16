// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/GridBase.h"

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

