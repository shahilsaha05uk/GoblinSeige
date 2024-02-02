// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	SpawnEnemyControllers();
}

void AEnemyManager::OnRequestEnemy()
{
	int TotalEnemies, TotalEnemiesPerSpawnPoints;
	GetRandomEnemyCounts(TotalEnemies, TotalEnemiesPerSpawnPoints);
	
	for (auto s : SpawnPoints)
	{
		for (int i = 0; i< TotalEnemiesPerSpawnPoints; i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawning Enemy"));
			AllocateController(s);
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
}

void AEnemyManager::FreeController(AEnemyController* ControllerToFree)
{
	auto id = ControllerToFree->GetID();
	if (AllocatedController.Contains(id))
	{
		AvailableController.Enqueue(ControllerToFree);
		AllocatedController.Remove(id);
	}
}

void AEnemyManager::SpawnEnemyControllers()
{
	for (int i= 0; i < 100; i++)
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
