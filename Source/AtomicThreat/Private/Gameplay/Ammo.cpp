// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Ammo.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Gameplay/RocketMeshActor.h" // < delete
#include "Containers/Array.h"

AAmmo::AAmmo()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneRoot);
	StaticMesh->SetRelativeLocation(FVector(0.f, 0.f, 200.f));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(SceneRoot);
	Arrow->SetRelativeLocation(FVector(250.f, 0.f, 200.f));

	Zero = CreateDefaultSubobject<USceneComponent>(TEXT("Zero"));
	Zero->SetupAttachment(SceneRoot);
	Zero->SetRelativeLocation(FVector(0.f, 20.f, 100.f));

	Even = CreateDefaultSubobject<USceneComponent>(TEXT("Even"));
	Even->SetupAttachment(SceneRoot);
	Even->SetRelativeLocation(FVector(0.f, 320.f, 100.f));

	Odd = CreateDefaultSubobject<USceneComponent>(TEXT("Odd"));
	Odd->SetupAttachment(SceneRoot);
	Odd->SetRelativeLocation(FVector(0.f, -280.f, 100.f));

	/*for (int32 i = 1; i < AmmoAmount; i++)
	{
		//FString NewName = FString("RocketMeshComponent") + ;
		FName NewName = FName(TEXT("RocketMeshComponent %d"), i);
		UStaticMeshComponent* NewStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(NewName);
		Rockets.Add(NewStaticMesh);
		NewStaticMesh->SetupAttachment(GetRootComponent());

		FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);

		if (i == 1)
		{
			NewStaticMesh->AttachToComponent(Zero, TransformRules);
		}
		else if ((i % 2) > 0)
		{
			NewStaticMesh->SetRelativeLocation(FVector(0.f, UKismetMathLibrary::Multiply_VectorInt(Odd->GetRelativeLocation(), Odd->GetNumChildrenComponents()).Y, 0.f), false, nullptr);
			NewStaticMesh->AttachToComponent(Odd, TransformRules);
		}
		else
		{
			NewStaticMesh->SetRelativeLocation(FVector(0.f, UKismetMathLibrary::Multiply_VectorInt(Even->GetRelativeLocation(), Even->GetNumChildrenComponents()).Y, 0.f), false, nullptr);
			NewStaticMesh->AttachToComponent(Even, TransformRules);
		}

	}*/
	
}

bool AAmmo::UseAmmo()
{
	//Rockets.Is
	if (!Rockets.IsValidIndex(0))
		return false;

	Rockets.Last()->DestroyComponent();
	Rockets.RemoveSingle(Rockets.Last());

	return true;
}

void AAmmo::BeginPlay()
{
	Super::BeginPlay();

	RefillAmmo();
}

void AAmmo::RefillAmmo() //Delete
{
	/*for (UStaticMeshComponent* TStaticMesh : Rockets)
	{
		TStaticMesh->SetStaticMesh(AmmoMesh);
	}*/
	for (size_t i = 1; i < AmmoAmount; i++)
	{
		//Rockets.Add((&NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass()));
		UStaticMeshComponent* NewStaticMesh = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
		NewStaticMesh->RegisterComponent(); //read about this
		NewStaticMesh->SetStaticMesh(AmmoMesh);

		FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);

		if (i == 1)
		{
			NewStaticMesh->AttachToComponent(Zero, TransformRules);
		}
		else if ((i % 2) > 0)
		{
			NewStaticMesh->SetRelativeLocation(FVector(0.f, UKismetMathLibrary::Multiply_VectorInt(Odd->GetRelativeLocation(), Odd->GetNumChildrenComponents()).Y, 0.f), false, nullptr);
			NewStaticMesh->AttachToComponent(Odd, TransformRules);
		}
		else
		{
			NewStaticMesh->SetRelativeLocation(FVector(0.f, UKismetMathLibrary::Multiply_VectorInt(Even->GetRelativeLocation(), Even->GetNumChildrenComponents()).Y, 0.f), false, nullptr);
			NewStaticMesh->AttachToComponent(Even, TransformRules);
		}

		Rockets.Add(NewStaticMesh);
	}
}

void AAmmo::ClearAmmo()
{
	for (UStaticMeshComponent* TRocket : Rockets) // small bug here check when changing parametrs in editor
		TRocket->DestroyComponent();

	Rockets.Empty();
}

int32 AAmmo::AmmoLeft() //TODO: delete after fixing attached actros in RefillAmmo()
{
	return Rockets.Num();
}

void AAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

