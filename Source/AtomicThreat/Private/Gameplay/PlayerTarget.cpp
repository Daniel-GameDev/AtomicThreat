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

void ATargetBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerTarget::RotateTarget(float DeltaTime)
{
	float Roll = (MeshScene->GetRelativeRotation().Roll + RollValue) * DeltaTime;
	MeshScene->SetRelativeRotation(FRotator(0.f, 0.f, Roll));
}
