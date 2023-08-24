// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/AtomicPlayerController.h"
#include "Blueprint/UserWidget.h"

void AAtomicPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	CreateUserWidget(StartWidget);
}

void AAtomicPlayerController::CreateUserWidget(TSubclassOf<UUserWidget> Widget)
{
	if (Widget)
	{
		UUserWidget* WidgetToCreate = CreateWidget<UUserWidget>(GetWorld(), Widget);
		WidgetToCreate->AddToViewport();
	}
}
