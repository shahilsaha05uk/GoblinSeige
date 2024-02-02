// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

#include "ManagerClasses/EnemyManager.h"

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(BehaviorTreeRef);
}

void AEnemyController::OnSpawn(AEnemyManager* Manager)
{
	Manager->OnEnemySpawnRequest.AddDynamic(this, &AEnemyController::OnPawnSpawnRequest);

	UniqueID = GetUniqueID();
}

void AEnemyController::SpawnPawn_Implementation(AEnemySpawnPoint* SpawnBox)
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning Enemies"));
}

void AEnemyController::OnPawnSpawnRequest_Implementation(AEnemySpawnPoint* SpawnBox)
{
	
}
