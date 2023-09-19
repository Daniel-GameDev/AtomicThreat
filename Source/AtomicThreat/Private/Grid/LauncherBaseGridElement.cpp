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

void ALauncherBaseGridElement::LaunchRocket(TSubclassOf<ARocketBase> RocketType, FTransform TargetTransform, float DifficultyIncrement, APlayerController* PlayerController)
{
	if (GetWorld())
	{
		FVector Location = LaunchPoint->GetComponentLocation();
		AActor* RocketActor = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, RocketType, FTransform(Location), ESpawnActorCollisionHandlingMethod::Undefined, nullptr);
		
		if (ARocketBase* RocketBase = Cast<ARocketBase>(RocketActor))
		{
			RocketBase->TargetTransform = TargetTransform;
			RocketBase->DifficultyIncrement = DifficultyIncrement;
			RocketBase->PlayerController = PlayerController;
			RocketBase->SetActorRotation(LaunchPoint->GetComponentRotation());
			RocketBase->SetProjectileSettings();
		}
		UGameplayStatics::FinishSpawningActor(RocketActor, FTransform(Location));
	}
}

void ALauncherBaseGridElement::LaunchMultiRocket(TSubclassOf<ARocketBase> RocketType, FVector TargetVector, TArray<FVector> TargetVectors, float DifficultyIncrement)
{
	if (GetWorld())
	{
		FVector Location = LaunchPoint->GetComponentLocation();
		AActor* RocketActor = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, RocketType, FTransform(Location), ESpawnActorCollisionHandlingMethod::Undefined, nullptr);

		if (ARocketBase* RocketBase = Cast<ARocketBase>(RocketActor))
		{
			RocketBase->TargetTransform.SetLocation(TargetVector);
			RocketBase->DifficultyIncrement = DifficultyIncrement;
			RocketBase->TargetVectors = TargetVectors;
		}
		UGameplayStatics::FinishSpawningActor(RocketActor, FTransform(Location));
	}
}
