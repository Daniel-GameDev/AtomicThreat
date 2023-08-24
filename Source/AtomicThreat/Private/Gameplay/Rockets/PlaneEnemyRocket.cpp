// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Rockets/PlaneEnemyRocket.h"

APlaneEnemyRocket::APlaneEnemyRocket()
{
	AttachedRocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AttachedRocketMesh"));
	AttachedRocketMesh->SetupAttachment(GetRootComponent());
}

void APlaneEnemyRocket::BeginDecay()
{
	SpawnRockets(false);
	AttachedRocketMesh->DestroyComponent();
}

int32 APlaneEnemyRocket::GetPoints()
{
	return Points;
}

void APlaneEnemyRocket::SetPoints(int32 NewPoints)
{
}
