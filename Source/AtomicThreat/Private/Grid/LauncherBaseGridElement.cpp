// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/LauncherBaseGridElement.h"
#include "Kismet/GameplayStatics.h"
#include "Gameplay/Rockets/RocketBase.h"

ALauncherBaseGridElement::ALauncherBaseGridElement()
{
	RocketLauncherMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RocketLauncherMesh"));
	RocketLauncherMesh->SetupAttachment(GridMesh);

	LaunchPoint = CreateDefaultSubobject<USceneComponent>(TEXT("LaunchPoint"));
	LaunchPoint->SetupAttachment(GetRootComponent());
}

void ALauncherBaseGridElement::LaunchRocket(TSubclassOf<ARocketBase> RocketType, FVector TargetVector, float DifficultyIncrement)
{
	if (GetWorld())
	{
		AActor* RocketActor = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), RocketType, FTransform(LaunchPoint->GetComponentLocation()), ESpawnActorCollisionHandlingMethod::Undefined, nullptr);
		
		if (ARocketBase* RocketBase = Cast<ARocketBase>(RocketActor))
		{
			RocketBase->TargetVector = TargetVector;
			RocketBase->DifficultyIncrement = DifficultyIncrement;
		}

		UGameplayStatics::FinishSpawningActor(RocketActor, FTransform(LaunchPoint->GetComponentLocation()));
	}
}
