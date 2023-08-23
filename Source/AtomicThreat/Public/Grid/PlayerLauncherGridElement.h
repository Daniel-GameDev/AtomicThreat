// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid/LauncherBaseGridElement.h"
#include "PlayerLauncherGridElement.generated.h"

class AAtomicPawn;
class AAmmo;
class UCapsuleComponent;

UCLASS()
class ATOMICTHREAT_API APlayerLauncherGridElement : public ALauncherBaseGridElement
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	APlayerLauncherGridElement();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* DestroyedLauncherMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCapsuleComponent* LauncherCapsule;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AAtomicPawn> AtomicPawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AAmmo> AmmoClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector AmmoDisplayLocation = FVector(-900.f, 0.f, -450.f);

	UFUNCTION()
	void SpawnAtomicPawn(APlayerController* PlayerController);

	UFUNCTION()
	void RestoreLauncher();

	UFUNCTION(BlueprintCallable)
		void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

public:
	virtual void LaunchRocket(TSubclassOf<ARocketBase> RocketType, FVector TargetVector, float DifficultyIncrement) override;

	UFUNCTION()
	void SpawnAmmo();

	UFUNCTION()
	void DestroyAmmo();

private:
	UPROPERTY()
	AAmmo* Ammo;

};
