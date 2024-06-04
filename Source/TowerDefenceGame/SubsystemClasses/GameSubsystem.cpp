// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSubsystem.h"


#pragma region Spawn points

void UGameSubsystem::RegisterSpawnPoint(AEnemySpawnPoint* SpawnPoint)
{
	if(!mSpawnPoints.Contains(SpawnPoint))
	{
		mSpawnPoints.Add(SpawnPoint);
		EnemySpawnPointCount++;
	}
}

void UGameSubsystem::DeRegisterSpawnPoint(AEnemySpawnPoint* SpawnPoint)
{
	if(mSpawnPoints.Contains(SpawnPoint))
	{
		mSpawnPoints.Remove(SpawnPoint);
		EnemySpawnPointCount--;
	}
}

AEnemySpawnPoint* UGameSubsystem::GetRandomEnemySpawnPoint()
{
	int rand = FMath::RandRange(0, EnemySpawnPointCount -1);
	return mSpawnPoints[rand];
}

#pragma endregion
