// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/DefenceExplosion.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/TimelineComponent.h"

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

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f - timelineValue"), ExpSize));

	if (UKismetSystemLibrary::SphereTraceSingleByProfile(GetWorld(), GetActorLocation(), GetActorLocation(), Size * ExpSize, FName("Explosion"),
		false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Red, FLinearColor::Green, 0.f))
	{
		HitResult.GetComponent()->GetOwner()->Destroy(); // Add interface for points
	};
	
}

void ADefenceExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeline.TickTimeline(DeltaTime);

}
