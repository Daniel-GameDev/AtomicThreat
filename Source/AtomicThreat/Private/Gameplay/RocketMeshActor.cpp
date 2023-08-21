// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/RocketMeshActor.h"

// Sets default values
ARocketMeshActor::ARocketMeshActor() // < delete
{
	PrimaryActorTick.bCanEverTick = false;

	RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>("RocketMesh");
	SetRootComponent(RocketMesh);

}
void ARocketMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

