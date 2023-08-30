// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Rockets/EnemyRocket.h"
#include "Components/CapsuleComponent.h"

AEnemyRocket::AEnemyRocket()
{
	RocketCapsule->SetCollisionProfileName(FName("EnemyCollision"));
}

int32 AEnemyRocket::GetPoints()
{
	return Points;
}
