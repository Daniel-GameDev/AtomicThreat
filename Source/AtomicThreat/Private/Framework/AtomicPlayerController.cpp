// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/AtomicPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Framework/AtomicPlayerState.h"

void AAtomicPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	CreateUserWidget(StartWidget);
	GetPlayerState<AAtomicPlayerState>()->CurrentPlayer = this;
}

void AAtomicPlayerController::CreateUserWidget(TSubclassOf<UUserWidget> Widget)
{
	FInputModeUIOnly InputMode;
	SetInputMode(InputMode);

	if (Widget)
	{
		UUserWidget* WidgetToCreate = CreateWidget<UUserWidget>(GetWorld(), Widget);
		WidgetToCreate->AddToViewport();
	}
}

void AAtomicPlayerController::StartCameraShake()
{
	PlayerCameraManager->StartCameraShake(AtomicShakeClass);
}
