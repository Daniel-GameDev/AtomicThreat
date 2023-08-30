// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Rockets/RocketBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Gameplay/TargetBase.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Framework/AtomicGameMode.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

ARocketBase::ARocketBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RocketSceneRoot"));
	SetRootComponent(SceneRoot);

	RocketForward = CreateDefaultSubobject<UArrowComponent>(TEXT("RocketForward"));
	RocketForward->SetupAttachment(GetRootComponent());

	RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RocketMesh"));
	RocketMesh->SetupAttachment(RocketForward);
	RocketMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RocketSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RocketSkeletalMesh"));
	RocketSkeletalMesh->SetupAttachment(RocketForward);

	RocketCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RocketCpasule"));
	RocketCapsule->SetupAttachment(RocketForward);
	RocketCapsule->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("RocketNiagaraComponent"));
	NiagaraComponent->SetupAttachment(RocketForward);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->bIsHomingProjectile = true;
}

void ARocketBase::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		if (AAtomicGameMode* GameMode = Cast<AAtomicGameMode>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->TotalRocketsLeft(true);
		}

		SetProjectileSettings();
		StartPoint = PreviousPoint = GetActorLocation();
		CreateTarget();
	}
}

void ARocketBase::CreateTarget()
{
	if (Target)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		TargetSceneRoot = GetWorld()->SpawnActor<ATargetBase>(Target, TargetTransform.GetLocation(), TargetTransform.GetRotation().Rotator(), SpawnParams)->GetRootComponent();
		ProjectileMovement->HomingTargetComponent = TargetSceneRoot;
	}
}

void ARocketBase::DrawDebugLineRocketTrajectory()
{
	DrawDebugLine(GetWorld(), PreviousPoint, GetActorLocation(), FColor::Red, false, 1.5f, 0U, 20.f);
	PreviousPoint = GetActorLocation();
}

void ARocketBase::DrawDebugLineFromStartToEnd()
{
	DrawDebugLine(GetWorld(), StartPoint, TargetTransform.GetLocation(), FColor::Blue, false, 5.f, 0U, 50.f);
}

void ARocketBase::RocketRotation(float DeltaTime)
{
	RocketForward->SetRelativeRotation(FRotator(0.f, 0.f, DeltaTime*RotationSpeed+RocketForward->GetRelativeRotation().Roll));
}

void ARocketBase::TargetHit()
{
	this->Destroy();
}

void ARocketBase::SetProjectileSettings()
{
	ProjectileMovement->InitialSpeed = this->InitialSpeed * DifficultyIncrement;
	ProjectileMovement->MaxSpeed = this->MaxSpeed * DifficultyIncrement;
	ProjectileMovement->HomingAccelerationMagnitude = this->HomingAccelerationMagnitude;
}

void ARocketBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RocketRotation(DeltaTime);

	if (UKismetMathLibrary::EqualEqual_VectorVector(GetActorLocation(), TargetTransform.GetLocation(), ToleranceTargetCoordinate))
	{
		TargetHit();
	}

	if (bDrawDebugLineRocketTrajectory)
	{
		DrawDebugLineRocketTrajectory();
	}

	if (bDrawDebugLineFromStartToEnd)
	{
		DrawDebugLineFromStartToEnd();
	}
}

void ARocketBase::Destroyed()
{
	if (TargetSceneRoot)
	{
		TargetSceneRoot->GetOwner()->Destroy();
	}

	if (AAtomicGameMode* GameMode = Cast<AAtomicGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->TotalRocketsLeft(false);
	}

	if (GetWorld() && DestroyParticle && bSpawnDestroyedParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, FTransform(GetActorRotation(), GetActorLocation(), FVector(DestroyParticleScale)));
	}

	Super::Destroyed();
}

