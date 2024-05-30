// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySubsystem.h"

#include "Kismet/KismetMathLibrary.h"
#include "TowerDefenceGame/ControllerClasses/EnemyController.h"

#pragma region Register Spawn Points

void UEnemySubsystem::RegisterSpawnPoint(AEnemySpawnPoint* SpawnPoint)
{
	if(!mSpawnPoints.Contains(SpawnPoint))
	{
		mSpawnPoints.Add(SpawnPoint);
		EnemySpawnPointCount++;
	}
}

void UEnemySubsystem::DeRegisterSpawnPoint()
{
	mSpawnPoints.Empty();
}


#pragma endregion

#pragma region Getters

AEnemySpawnPoint* UEnemySubsystem::GetRandomEnemySpawnPoint()
{
	int rand = FMath::RandRange(0, EnemySpawnPointCount);
	return mSpawnPoints[rand];
}

#pragma endregion