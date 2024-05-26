// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnPoint.h"

#include "TowerDefenceGame/SubsystemClasses/EnemySubsystem.h"


FVector AEnemySpawnPoint::GetRandomPointInsideTheSpawnArea_Implementation()
{
	return FVector(0, 0, 0);
}

void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	GetGameInstance()->GetSubsystem<UEnemySubsystem>()->RegisterSpawnPoint(this);
}
