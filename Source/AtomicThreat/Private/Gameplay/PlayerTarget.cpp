// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/PlayerTarget.h"

APlayerTarget::APlayerTarget()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshScene = CreateDefaultSubobject<USceneComponent>(TEXT("MeshSceneComponent"));
	MeshScene->SetupAttachment(SceneRoot);

	TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetMesh"));
	TargetMesh->SetupAttachment(MeshScene);
}

void APlayerTarget::RotateTarget(float Tick)
{
	float Roll = MeshScene->GetRelativeRotation().Roll + RollValue * Tick;
	MeshScene->SetRelativeRotation(FRotator(0.f, 0.f, Roll));
}

void APlayerTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateTarget(DeltaTime);
}
