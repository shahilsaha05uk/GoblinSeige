// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "TowerDefenceGame/SubsystemClasses/EnemySubsystem.h"

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
}


void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AEnemyController::OnUnPossess()
{
	Super::OnUnPossess();
	if(const auto enemySubs = GetGameInstance()->GetSubsystem<UEnemySubsystem>())
	{
		enemySubs->OnEnemyDead.Broadcast(this);
	}
}

void AEnemyController::SpawnPawn_Implementation(AEnemySpawnPoint* SpawnBox, int Type)
{

}

void AEnemyController::EnemyMove_Implementation(FVector TargetLocation)
{
	
}

void AEnemyController::EnemyAttack_Implementation()
{
	
}

