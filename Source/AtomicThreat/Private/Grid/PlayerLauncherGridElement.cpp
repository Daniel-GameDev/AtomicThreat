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

void APlayerLauncherGridElement::Recovery()
{
	RestoreLauncher();
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
	if (bDestroyed && Ammo)
	{
		Ammo->RefillAmmo();
		bDestroyed = false;
		RocketLauncherMesh->SetVisibility(true);
		DestroyedLauncherMesh->SetVisibility(false);
	}
	else if (!bDestroyed && Ammo)
	{
		Ammo->ClearAmmo();
		Ammo->RefillAmmo();
	}
		
}

void APlayerLauncherGridElement::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	Destroyed();
}

void APlayerLauncherGridElement::LaunchRocket(TSubclassOf<ARocketBase> RocketType, FTransform TargetTransform, float DifficultyIncrement, APlayerController* PlayerController)
{
	if (Ammo->UseAmmo())
	{
		Super::LaunchRocket(RocketType, TargetTransform, DifficultyIncrement, PlayerController);
	}

}

void APlayerLauncherGridElement::SpawnAmmo()
{
	if (AmmoClass)
	{
		FActorSpawnParameters SpawnParam;
		Ammo = GetWorld()->SpawnActor<AAmmo>(AmmoClass, FVector(AmmoDisplayLocation.X, 0.f, AmmoDisplayLocation.Z), FRotator(0.f, 0.f, 0.f), SpawnParam);

		FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
		Ammo->AttachToActor(this, TransformRules);
		//Ammo->SetActorLocation(); //Ammo->GetActorLocation().Y
		//Ammo->SetActorRotation();

	}
	
}

void APlayerLauncherGridElement::Destroyed()
{
	if (!bDestroyed && Ammo)
	{
		Ammo->ClearAmmo();
		bDestroyed = true;
		RocketLauncherMesh->SetVisibility(false);
		DestroyedLauncherMesh->SetVisibility(true);
	}

	Super::Destroyed();
}

int32 APlayerLauncherGridElement::GetPoints()
{
	return Ammo->AmmoLeft() * Points;
}