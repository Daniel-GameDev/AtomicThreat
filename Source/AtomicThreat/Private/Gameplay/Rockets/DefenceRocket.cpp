// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Rockets/DefenceRocket.h"
#include "Gameplay/DefenceExplosion.h"

void ADefenceRocket::Destroyed()
{
	SpawnExplosion();

	Super::Destroyed();
}

void ADefenceRocket::SpawnExplosion()
{
	FActorSpawnParameters SpawnParams;
	ADefenceExplosion* DefenceExp = GetWorld()->SpawnActor<ADefenceExplosion>(Explosion, TargetVector, FRotator(), SpawnParams);
	DefenceExp->PlayerController = PlayerController;
}
