// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Rockets/DefenceRocket.h"
#include "Gameplay/DefenceExplosion.h"
#include "Components/CapsuleComponent.h"

ADefenceRocket::ADefenceRocket()
{
	PrimaryActorTick.bCanEverTick = true;

	RocketCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ADefenceRocket::Destroyed()
{
	SpawnExplosion();

	Super::Destroyed();
}

void ADefenceRocket::SpawnExplosion()
{
	FActorSpawnParameters SpawnParams;
	ADefenceExplosion* DefenceExp = GetWorld()->SpawnActor<ADefenceExplosion>(Explosion, TargetTransform.GetLocation(), TargetTransform.GetRotation().Rotator(), SpawnParams);
	DefenceExp->PlayerController = PlayerController;
}
