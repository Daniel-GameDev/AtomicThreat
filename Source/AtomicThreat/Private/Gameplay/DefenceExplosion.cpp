// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/DefenceExplosion.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/TimelineComponent.h"

ADefenceExplosion::ADefenceExplosion()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADefenceExplosion::TimelineProgress(float Value)
{
}

void ADefenceExplosion::BeginPlay()
{
	Super::BeginPlay();

	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		CurveTimeline.SetLooping(true);
	}
	
}

void ADefenceExplosion::TraceExplosion(float ExpSize)
{
	//UKismetSystemLibrary::SphereTraceSingleByProfile
}

void ADefenceExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

