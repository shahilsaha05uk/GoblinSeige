// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	SpawnEnemyControllers(1);
}

void AEnemyManager::OnRequestEnemy()
{
	int TotalEnemies, TotalEnemiesPerSpawnPoints;
	GetRandomEnemyCounts(TotalEnemies, TotalEnemiesPerSpawnPoints);

	// if the enemy count is more than the controller count, spawn more controllers
	if(TotalEnemies > TotalControllersAvailable) SpawnEnemyControllers(TotalEnemies - TotalControllersAvailable + 1);

	
	for (auto s : SpawnPoints)
	{
		for (int i = 0; i< TotalEnemiesPerSpawnPoints; i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawning Enemy"));
			AllocateController(s);

			TotalControllersAvailable++;
		}
	}
}

void AEnemyManager::AllocateController(AEnemySpawnPoint* sb)
{
	if(AvailableController.IsEmpty()) return;

	AEnemyController* outItem;
	AvailableController.Dequeue(outItem);
	outItem->SpawnPawn(sb);

	auto id = outItem->GetID();
	AllocatedController.Add(id, outItem);

	TotalControllersAvailable--;
}

void AEnemyManager::FreeController(AEnemyController* ControllerToFree)
{
	auto id = ControllerToFree->GetID();
	if (AllocatedController.Contains(id))
	{
		AvailableController.Enqueue(ControllerToFree);
		AllocatedController.Remove(id);

		TotalControllersAvailable++;
	}
}

void AEnemyManager::SpawnEnemyControllers(int Count)
{
	for (int i= 0; i < Count; i++)
	{
		AEnemyController* NewController = GetWorld()->SpawnActor<AEnemyController>(EnemyControllerClass);
		NewController->OnSpawn(this);
		AvailableController.Enqueue(NewController);
	}
}

void AEnemyManager::GetRandomEnemyCounts(int& TotalEnemies, int& TotalEnemiesPerSpawnPoints)
{
	TotalEnemies = UKismetMathLibrary::RandomIntegerInRange(EnemyMinRange, EnemyMaxRange);
	TotalEnemiesPerSpawnPoints = TotalEnemies / SpawnPoints.Num();
}
