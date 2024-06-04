// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySubsystem.h"

#pragma region Register Spawn Points

void UEnemySubsystem::RegisterSpawnPoint(AEnemySpawnPoint* SpawnPoint)
{
	if(!mSpawnPoints.Contains(SpawnPoint))
	{
		mSpawnPoints.Add(SpawnPoint);
		EnemySpawnPointCount++;
	}
}

void UEnemySubsystem::DeRegisterSpawnPoint(AEnemySpawnPoint* SpawnPoint)
{
	if(mSpawnPoints.Contains(SpawnPoint))
	{
		mSpawnPoints.Remove(SpawnPoint);
		EnemySpawnPointCount--;
	}
}

#pragma endregion

#pragma region Getters

AEnemySpawnPoint* UEnemySubsystem::GetRandomEnemySpawnPoint()
{
	int rand = FMath::RandRange(0, EnemySpawnPointCount -1);
	return mSpawnPoints[rand];
}

#pragma endregion