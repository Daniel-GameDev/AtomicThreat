// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/DefenceExplosion.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/TimelineComponent.h"
#include "Common/PointsInterface.h"
#include "Framework/AtomicPlayerState.h"

ADefenceExplosion::ADefenceExplosion()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADefenceExplosion::BeginPlay()
{
	Super::BeginPlay();

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

	if (UKismetSystemLibrary::SphereTraceSingleByProfile(GetWorld(), GetActorLocation(), GetActorLocation(), Size * ExpSize, FName("Explosion"),
		false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Red, FLinearColor::Green, 0.f))
	{
		int32 Points = 0;
		if (IPointsInterface* Interface = Cast<IPointsInterface>(HitResult.GetComponent()->GetOwner()))
			Points = Interface->GetPoints();

		if (IPointsInterface* Interface = Cast<IPointsInterface>(PlayerController->GetPlayerState<AAtomicPlayerState>()))
			Interface->SetPoints(Points);

		HitResult.GetComponent()->GetOwner()->Destroy();
	}
	
}

void ADefenceExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurveTimeline.TickTimeline(DeltaTime);

}

