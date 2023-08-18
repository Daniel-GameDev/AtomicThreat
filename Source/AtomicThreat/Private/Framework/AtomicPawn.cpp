// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/AtomicPawn.h"
#include "Framework/AtomicPlayerController.h"
#include "Grid/PlayerLauncherGridElement.h"

AAtomicPawn::AAtomicPawn() //DELETE !!!
{
	PrimaryActorTick.bCanEverTick = true;

	AtomicPlayerController = Cast<AAtomicPlayerController>(GetController());
}

void AAtomicPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAtomicPawn::Launch()
{
	FHitResult HitResult;

	if (AtomicPlayerController->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), true, HitResult))
	{
		TSubclassOf<ARocketBase> Rocket; //TODO: Property for BP_Rocket to set in pawn defaults
		PlayerLauncherGridElement->LaunchRocket(Rocket, HitResult.Location, 1.f); //TODO: Difficulty Increment - create Property for pawn
	}
}

void AAtomicPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAtomicPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Launch", IE_Pressed, this, &AAtomicPawn::Launch);

}

