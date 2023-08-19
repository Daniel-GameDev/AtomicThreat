// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/PlayerLauncherGridElement.h"
#include "Framework/AtomicPawn.h"
#include "Kismet/GameplayStatics.h"

void APlayerLauncherGridElement::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
		SpawnAtomicPawn(UGameplayStatics::GetPlayerController(GetWorld(), 0));

}

void APlayerLauncherGridElement::SpawnAtomicPawn(APlayerController* PlayerController)
{
	AActor* AtomicPawnActor = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), AtomicPawn, FTransform(GetActorTransform()), ESpawnActorCollisionHandlingMethod::Undefined, nullptr);

	if (AAtomicPawn* NewAtomicPawn = Cast<AAtomicPawn>(AtomicPawnActor))
	{
		NewAtomicPawn->PlayerLauncherGridElement = this;
		PlayerController->Possess(NewAtomicPawn);
	}

	UGameplayStatics::FinishSpawningActor(AtomicPawnActor, FTransform(GetActorTransform()));

}
