// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnPoint.h"

#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"


void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();

}

FVector AEnemySpawnPoint::GetRandomPointWithinTheBounds_Implementation()
{
	return FVector(0, 0, 0);
}
