// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Rockets/RocketBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Gameplay/TargetBase.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

ARocketBase::ARocketBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RocketForward = CreateDefaultSubobject<UArrowComponent>(TEXT("RocketForward"));
	RocketForward->SetupAttachment(GetRootComponent());

	RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RocketMesh"));
	RocketMesh->SetupAttachment(RocketForward);

	RocketCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RocketCpasule"));
	RocketCapsule->SetupAttachment(RocketMesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = this->InitialSpeed * DifficultyIncrement;
	ProjectileMovement->MaxSpeed = this->MaxSpeed * DifficultyIncrement;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->bIsHomingProjectile = true;
	ProjectileMovement->HomingAccelerationMagnitude = this->HomingAccelerationMagnitude;

}

void ARocketBase::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		StartPoint, PreviousPoint = GetActorLocation();

		CreateTarget(); //TODO: Rocket Notife Func for creation / destroy
	}
}

void ARocketBase::CreateTarget()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	TargetSceneRoot = GetWorld()->SpawnActor<ATargetBase>(Target, TargetVector, FRotator(), SpawnParams)->GetRootComponent();
	ProjectileMovement->HomingTargetComponent = TargetSceneRoot;
}

void ARocketBase::DrawDebugLineRocketTrajectory()
{
	DrawDebugLine(GetWorld(), PreviousPoint, GetActorLocation(), FColor::Red, false, 1.5f, 0U, 20.f);
	PreviousPoint = GetActorLocation();
}

void ARocketBase::DrawDebugLineFromStartToEnd()
{
	DrawDebugLine(GetWorld(), StartPoint, TargetVector, FColor::Blue, false, 5.f, 0U, 50.f);
}

void ARocketBase::RocketRotation(float DeltaTime)
{
	RocketForward->SetRelativeRotation(FRotator(DeltaTime*RotationSpeed+RocketForward->GetRelativeRotation().Roll, 0.f, 0.f));
}

void ARocketBase::TargetHit()
{
	this->Destroy();
}

void ARocketBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RocketRotation(DeltaTime);

	if (UKismetMathLibrary::EqualEqual_VectorVector(GetActorLocation(), TargetVector, ToleranceTargetCoordinate))
		TargetHit();

	if (bDrawDebugLineRocketTrajectory)
		DrawDebugLineRocketTrajectory();

	if (bDrawDebugLineFromStartToEnd)
		DrawDebugLineFromStartToEnd();
}

void ARocketBase::Destroyed()
{
	//TODO: Rocket Notify Func - destroyed
	TargetSceneRoot->GetOwner()->Destroy();

	Super::Destroyed();
}
