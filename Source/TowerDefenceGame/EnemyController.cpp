// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

#include "BaseClasses/BaseEnemy.h"
#include "ManagerClasses/EnemyManager.h"
#include "Navigation/PathFollowingComponent.h"

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(BehaviorTreeRef);
}

void AEnemyController::OnSpawn(AEnemyManager* Manager)
{
	mEnemyManager = Manager;
	Manager->OnEnemySpawnRequest.AddDynamic(this, &AEnemyController::SpawnPawn);
	Manager->OnControllerDestroySignature.AddDynamic(this, &AEnemyController::OnControllerDestroy);
}

void AEnemyController::EnemyMove_Implementation(FVector TargetLocation)
{
	
}

void AEnemyController::EnemyAttack_Implementation()
{
	
}

bool AEnemyController::EnemyHasAValidPath_Implementation()
{
	return GetPathFollowingComponent()->HasValidPath();
}

void AEnemyController::OnDead_Implementation()
{
	UnPossess();

	mEnemyManager->FreeController();
}

void AEnemyController::OnControllerDestroy_Implementation()
{
	if(APawn* p = GetPawn())
	{
		p->Destroy();
		UnPossess();
	}
	Destroy();
}

void AEnemyController::SpawnPawn_Implementation(AEnemySpawnPoint* SpawnBox)
{
	EnemyRef->OnPawnDeadSignature.AddDynamic(this, &AEnemyController::OnDead);

	Possess(EnemyRef);
}
