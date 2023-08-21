// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Rockets/EnemyRocket.h"
#include "Components/CapsuleComponent.h"

AEnemyRocket::AEnemyRocket()
{
	//Super::GetParentActor();
	RocketCapsule->SetCollisionProfileName(FName("EnemyCollision"));
	RocketCapsule->OnComponentBeginOverlap.AddDynamic(this, &AEnemyRocket::OnCapsuleBeginOverlap);
}

void AEnemyRocket::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	Destroy();
}
