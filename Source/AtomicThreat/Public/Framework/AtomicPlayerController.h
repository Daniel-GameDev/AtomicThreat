// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "Blueprint/UserWidget.h"
#include "AtomicPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ATOMICTHREAT_API AAtomicPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> StartWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> GameLostWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> GameRoundWidget;

	UFUNCTION()
	void CreateUserWidget(TSubclassOf<UUserWidget> Widget);
	
};
