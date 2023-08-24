// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/AtomicPlayerState.h"
//#include "Framework/AtomicPlayerController.h"
//#include "Common/AtomicGameModeInterface.h"

int32 AAtomicPlayerState::GetPoints()
{
    return Points;
}

void AAtomicPlayerState::SetPoints(int32 NewPoints)
{
    Points += NewPoints * Bonus;
}

void AAtomicPlayerState::SetBonus(int32 BonusValue)
{
    Bonus = BonusValue;
}
