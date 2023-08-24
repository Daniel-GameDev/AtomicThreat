// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/PlayerLauncherGridElement.h"
#include "Framework/AtomicPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Gameplay/Ammo.h"
#include "Components/CapsuleComponent.h"

APlayerLauncherGridElement::APlayerLauncherGridElement()
{
	DestroyedLauncherMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DestroyedMesh"));
	DestroyedLauncherMesh->SetupAttachment(GridMesh);

	LauncherCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LauncherCapsule"));
	LauncherCapsule->SetupAttachment(GridMesh);
	LauncherCapsule->SetCollisionObjectType(ECC_GameTraceChannel3);
	LauncherCapsule->OnComponentBeginOverlap.AddDynamic(this, &APlayerLauncherGridElement::OnCapsuleBeginOverlap);
}

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

void APlayerLauncherGridElement::RestoreLauncher()
{
	if (bDestroyed)
	{
		Ammo->RefillAmmo();
		bDestroyed = false;
		RocketLauncherMesh->SetVisibility(true);
		DestroyedLauncherMesh->SetVisibility(false);
	}
}

void APlayerLauncherGridElement::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	Destroyed();
}

void APlayerLauncherGridElement::LaunchRocket(TSubclassOf<ARocketBase> RocketType, FVector TargetVector, float DifficultyIncrement, APlayerController* PlayerController)
{
	//AAmmo* AmmoToUse = Cast<AAmmo>(AmmoClass);
	if (Ammo->UseAmmo())
	{
		Super::LaunchRocket(RocketType, TargetVector, DifficultyIncrement, PlayerController);
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

void APlayerLauncherGridElement::Destroyed()
{
	if (!bDestroyed)
	{
		Ammo->ClearAmmo();
		bDestroyed = true;
		RocketLauncherMesh->SetVisibility(false);
		DestroyedLauncherMesh->SetVisibility(true);
	}
}
