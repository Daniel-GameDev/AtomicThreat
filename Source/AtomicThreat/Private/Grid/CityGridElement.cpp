// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/CityGridElement.h"
#include "Components/CapsuleComponent.h"

ACityGridElement::ACityGridElement()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultCityMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DefaultCityMesh"));
	DefaultCityMesh->SetupAttachment(GridMesh);

	DestroyedCityMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DestroyedCityMesh"));
	DestroyedCityMesh->SetupAttachment(GridMesh);

	CityCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CityCapsule"));
	CityCapsule->SetupAttachment(GridMesh);
	CityCapsule->SetCollisionProfileName(FName("CityCollision"));
	CityCapsule->SetCapsuleHalfHeight(300.f);
	CityCapsule->SetCapsuleRadius(300.f);
	CityCapsule->OnComponentBeginOverlap.AddDynamic(this, &ACityGridElement::OnCapsuleBeginOverlap);

	DestroyedCityMesh->SetVisibility(false);
	bDestroyed = false;
}

void ACityGridElement::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	bDestroyed = true;
	DefaultCityMesh->SetVisibility(false);
	DestroyedCityMesh->SetVisibility(true);
}

void ACityGridElement::RestoreCity()
{
	bDestroyed = false;
	DefaultCityMesh->SetVisibility(true);
	DestroyedCityMesh->SetVisibility(false);
}