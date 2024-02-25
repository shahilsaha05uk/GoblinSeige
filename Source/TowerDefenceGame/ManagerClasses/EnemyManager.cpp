// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"

#include "WaveManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "TowerDefenceGame/TowerDefenceGameGameModeBase.h"


void AEnemyManager::Init_Implementation(ATowerDefenceGameGameModeBase* gameMode)
{
	SpawnControllers(100);

	mGameMode = Cast<ATowerDefenceGameGameModeBase>(GetWorld()->GetAuthGameMode());
	mGameMode->OnGameOverSignature.AddDynamic(this, &AEnemyManager::OnGameOver);
}

void AEnemyManager::PrepareForWave_Implementation(int Wave)
{
	int NumberOfEnemiesToSpawn = GetRandomEnemyCounts(Wave);

	SpawnEnemies(NumberOfEnemiesToSpawn);
}

AEnemyController* AEnemyManager::GetFreeController()
{
	AEnemyController* outC;
	return (FreeControllers.Dequeue(outC))? outC : nullptr;
}

void AEnemyManager::AssignController(AEnemySpawnPoint* sb)
{
	FScopeLock Lock(&Mutex);
	
	if(FreeControllers.IsEmpty()) return;

	AEnemyController* freeController = GetFreeController();
	if(freeController!= nullptr) freeController->SpawnPawn(sb);
	else return;
	
	AllocatedControllers.Add(freeController);
}

void AEnemyManager::FreeController()
{
	TotalEnemiesDead++;
	mGameMode->OnEnemyKilledSignature.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Total Enemies Dead: %d"), TotalEnemiesDead);

	if(TotalEnemiesDead == AllocatedControllers.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Freeing the Controllers..."));

		for (auto C : AllocatedControllers)
		{
			FreeControllers.Enqueue(C);
		}

		AllocatedControllers.Empty(0);

		TotalEnemiesDead = 0;
		IGameModeInterface::Execute_GetWaveManager(mGameMode)->EndWave();
	}
}

int AEnemyManager::GetRandomEnemyCounts(int Wave)
{
	return UKismetMathLibrary::RandomIntegerInRange(Wave, (Wave + 2));
}

void AEnemyManager::SpawnControllers(int Count)
{
	for (int i= 0; i < Count; i++)
	{
		AEnemyController* NewController = GetWorld()->SpawnActor<AEnemyController>(EnemyControllerClass);
		NewController->OnSpawn(this);
		
		FreeControllers.Enqueue(NewController);
	}
}

void AEnemyManager::SpawnEnemies(int TotalEnemiesPerSpawnPoints)
{
	for (auto s : SpawnPoints)
	{
		for (int i = 0; i< TotalEnemiesPerSpawnPoints; i++)
		{
			AssignController(s);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Total Controller Assigned: %d"), AllocatedControllers.Num());
}

void AEnemyManager::OnGameOver_Implementation()
{
	OnControllerDestroySignature.Broadcast();

	if(!FreeControllers.IsEmpty()) FreeControllers.Empty();
	if(!AllocatedControllers.IsEmpty()) AllocatedControllers.Empty();
}

