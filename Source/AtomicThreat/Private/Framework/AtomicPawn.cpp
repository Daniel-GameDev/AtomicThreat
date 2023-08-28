// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/AtomicPawn.h"
#include "Framework/AtomicPlayerController.h"
#include "Grid/PlayerLauncherGridElement.h"
#include "Gameplay/Rockets/RocketBase.h"

AAtomicPawn::AAtomicPawn()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AAtomicPawn::BeginPlay()
{
	Super::BeginPlay();
	
	AtomicPlayerController = Cast<AAtomicPlayerController>(GetController());
}

void AAtomicPawn::Launch()
{
	FHitResult HitResult;
	if (AtomicPlayerController && Rocket)
		if (AtomicPlayerController->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), true, HitResult))
		{
			//HitResult.Location;
			//HitResult.Actor->GetActorRotation();
			FTransform TargetTransform(GetActorRotation(), HitResult.Location);
			PlayerLauncherGridElement->LaunchRocket(Rocket, TargetTransform, 1.f, AtomicPlayerController);
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

