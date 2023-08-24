// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/CityGrid.h"
#include "Grid/GridElementBase.h"

void ACityGrid::CreateBaseGird() // Delete
{
	Super::CreateBaseGird();

	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);

	for (int i = 0; i < AttachedActors.Num()-1; i++)
	{
		if (Cast<AGridElementBase>(AttachedActors[i])->bRecoveryRequiresPoints)
		{
			PointsElementsIndex.Add(i);
		}
	}
}
