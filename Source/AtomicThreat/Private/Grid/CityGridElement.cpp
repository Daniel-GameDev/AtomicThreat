// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/CityGridElement.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Common/AtomicGameModeInterface.h"
#include "GameFramework/GameModeBase.h"

ACityGridElement::ACityGridElement()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultCityMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DefaultCityMesh"));
	DefaultCityMesh->SetupAttachment(GridMesh);

	DestroyedCityMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DestroyedCityMesh"));
	DestroyedCityMesh->SetupAttachment(GridMesh);

	CityCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CityCapsule"));
	CityCapsule->SetupAttachment(GridMesh);
	CityCapsule->SetCollisionObjectType(ECC_GameTraceChannel3);
	CityCapsule->SetCapsuleHalfHeight(300.f);
	CityCapsule->SetCapsuleRadius(300.f);
	CityCapsule->OnComponentBeginOverlap.AddDynamic(this, &ACityGridElement::OnCapsuleBeginOverlap);

	DestroyedParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DestroyedParticle"));
	DestroyedParticle->SetupAttachment(DestroyedCityMesh);
	DestroyedParticle->SetHiddenInGame(true);

	DestroyedCityMesh->SetVisibility(false);
	bDestroyed = false;
}

void ACityGridElement::Recovery()
{
	if (bDestroyed)
		RestoreCity();
}

void ACityGridElement::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (GetWorld() && ExplosionParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, FTransform(GetActorRotation(), GetActorLocation(), FVector(ExplosionScale)));
		if (IAtomicGameModeInterface* Interface = Cast<IAtomicGameModeInterface>(GetWorld()->GetAuthGameMode()))
			Interface->StartPlayerCameraShake();
	}

	if (!bDestroyed)
		Destroyed();
}

void ACityGridElement::RestoreCity()
{
	bDestroyed = false;
	DefaultCityMesh->SetVisibility(true);
	DestroyedCityMesh->SetVisibility(false);
	DestroyedParticle->SetHiddenInGame(true);

}

void ACityGridElement::Destroyed()
{
	bDestroyed = true;
	DefaultCityMesh->SetVisibility(false);
	DestroyedCityMesh->SetVisibility(true);
	DestroyedParticle->SetHiddenInGame(false);
	Super::Destroyed();

}

int32 ACityGridElement::GetPoints()
{
	return Points;
}
