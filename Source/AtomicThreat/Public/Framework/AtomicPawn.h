// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AtomicPawn.generated.h"

class AAtomicPlayerController;
class APlayerLauncherGridElement;

UCLASS() //DELETE !!!
class ATOMICTHREAT_API AAtomicPawn : public APawn
{
	GENERATED_BODY()

public:
	AAtomicPawn();

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	APlayerLauncherGridElement* PlayerLauncherGridElement;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	AAtomicPlayerController* AtomicPlayerController;

	UFUNCTION(BlueprintCallable)
	void Launch();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
