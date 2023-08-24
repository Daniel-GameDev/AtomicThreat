// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Rockets/RocketBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Gameplay/TargetBase.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Common/AtomicGameModeInterface.h"
#include "GameFramework/GameModeBase.h"

ARocketBase::ARocketBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RocketSceneRoot"));
	SetRootComponent(SceneRoot);

	RocketForward = CreateDefaultSubobject<UArrowComponent>(TEXT("RocketForward"));
	RocketForward->SetupAttachment(GetRootComponent());

	RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RocketMesh"));
	RocketMesh->SetupAttachment(RocketForward);

	RocketCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RocketCpasule"));
	RocketCapsule->SetupAttachment(RocketMesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = this->InitialSpeed * DifficultyIncrement;
	ProjectileMovement->MaxSpeed = this->MaxSpeed * DifficultyIncrement;
	ProjectileMovement->HomingAccelerationMagnitude = this->HomingAccelerationMagnitude;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->bIsHomingProjectile = true;

}

void ARocketBase::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		if (IAtomicGameModeInterface* Interface = Cast<IAtomicGameModeInterface>(GetWorld()->GetAuthGameMode()))
			Interface->TotalRocketsLeft(true);

		SetProjectileSettings();

		StartPoint = PreviousPoint = GetActorLocation();
		//PreviousPoint = GetActorLocation();

		CreateTarget(); //TODO: Rocket Notife Func for creation / destroy
	}
}

void ARocketBase::CreateTarget()
{
	if (Target)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		TargetSceneRoot = GetWorld()->SpawnActor<ATargetBase>(Target, TargetVector, FRotator(), SpawnParams)->GetRootComponent();
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
	DrawDebugLine(GetWorld(), StartPoint, TargetVector, FColor::Blue, false, 5.f, 0U, 50.f);
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
	if (TargetSceneRoot)
		TargetSceneRoot->GetOwner()->Destroy();

	if (IAtomicGameModeInterface* Interface = Cast<IAtomicGameModeInterface>(GetWorld()->GetAuthGameMode()))
		Interface->TotalRocketsLeft(false);
	
	Super::Destroyed();
}

