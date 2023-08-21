// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/PlayerLauncherGridElement.h"
#include "Framework/AtomicPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Gameplay/Ammo.h"

void APlayerLauncherGridElement::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		SpawnAtomicPawn(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		SpawnAmmo();
	}
}

void APlayerLauncherGridElement::SpawnAtomicPawn(APlayerController* PlayerController)
{
	AActor* AtomicPawnActor = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), AtomicPawn, FTransform(GetActorTransform()), ESpawnActorCollisionHandlingMethod::Undefined, nullptr);

	if (AAtomicPawn* NewAtomicPawn = Cast<AAtomicPawn>(AtomicPawnActor))
	{
		NewAtomicPawn->PlayerLauncherGridElement = this;
		PlayerController->Possess(NewAtomicPawn);
	}

	UGameplayStatics::FinishSpawningActor(AtomicPawnActor, FTransform(GetActorTransform()));

}

void APlayerLauncherGridElement::LaunchRocket(TSubclassOf<ARocketBase> RocketType, FVector TargetVector, float DifficultyIncrement)
{
	//AAmmo* AmmoToUse = Cast<AAmmo>(AmmoClass);
	if (Ammo->UseAmmo())
	{
		Super::LaunchRocket(RocketType, TargetVector, DifficultyIncrement);
	}
	else
	{
		//TODO: Empty
	}

}

void APlayerLauncherGridElement::SpawnAmmo()
{
	if (AmmoClass)
	{
		FActorSpawnParameters SpawnParam;
		Ammo = GetWorld()->SpawnActor<AAmmo>(AmmoClass, GetActorLocation(), FRotator(), SpawnParam);

		FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
		Ammo->AttachToActor(this, TransformRules);
		Ammo->SetActorLocation(FVector(AmmoDisplayLocation.X, Ammo->GetActorLocation().Y, AmmoDisplayLocation.Z));
		Ammo->SetActorRotation(FRotator(0.f, 0.f, 0.f));

	}
	
}

void APlayerLauncherGridElement::DestroyAmmo() //Do I need this?
{
	Ammo->Destroy();
}
