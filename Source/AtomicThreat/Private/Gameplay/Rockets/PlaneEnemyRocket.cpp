// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Rockets/PlaneEnemyRocket.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/ArrowComponent.h"

APlaneEnemyRocket::APlaneEnemyRocket()
{
	AttachedRocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AttachedRocketMesh"));
	AttachedRocketMesh->SetupAttachment(RocketForward);

	SecondNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SecondNiagaraComponent"));
	SecondNiagaraComponent->SetupAttachment(RocketForward);
}

void APlaneEnemyRocket::BeginDecay()
{
	SpawnRockets(false);
	AttachedRocketMesh->DestroyComponent();
}

void APlaneEnemyRocket::TargetHit()
{
	bSpawnDestroyedParticle = false;
	Super::TargetHit();
}
