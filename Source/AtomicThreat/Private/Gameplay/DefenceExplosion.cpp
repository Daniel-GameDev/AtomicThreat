// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/DefenceExplosion.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/TimelineComponent.h"
#include "Common/PointsInterface.h"
#include "Framework/AtomicPlayerState.h"
#include "Framework/AtomicGameMode.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

ADefenceExplosion::ADefenceExplosion()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADefenceExplosion::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld() && ExplosionParticle)
	{
		float ExplosionScale = Size / SizeDevider;
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, FTransform(FRotator(), GetActorLocation(), FVector(ExplosionScale)));
	}

	if (AAtomicGameMode* GameMode = Cast<AAtomicGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->StartPlayerCameraShake();
	}

	if (CurveFloat)
	{
		FOnTimelineFloat TraceExplosion;
		TraceExplosion.BindUFunction(this, FName("TraceExplosion"));
		CurveTimeline.AddInterpFloat(CurveFloat, TraceExplosion);
		CurveTimeline.SetPlayRate(CurveTimeline.GetPlayRate() / Duration);
		CurveTimeline.Play();
	}
}

void ADefenceExplosion::TraceExplosion(float ExpSize)
{
	const TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;

	if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), GetActorLocation(), GetActorLocation(), Size * ExpSize, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Red, FLinearColor::Green, 0.f))
	{
		int32 Points = 0;
		if (IPointsInterface* Interface = Cast<IPointsInterface>(HitResult.GetComponent()->GetOwner()))
		{
			Points = Interface->GetPoints();
		}

		if (IPointsInterface* Interface = Cast<IPointsInterface>(PlayerController->GetPlayerState<AAtomicPlayerState>()))
		{
			Interface->SetPoints(Points);
		}
		HitResult.GetComponent()->GetOwner()->Destroy();
	}
}

void ADefenceExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurveTimeline.TickTimeline(DeltaTime);
}

