// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

#include "TowerDefenceGame/BaseClasses/BaseEnemy.h"
#include "Navigation/PathFollowingComponent.h"
#include "TowerDefenceGame/SubsystemClasses/EnemySubsystem.h"

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(BehaviorTreeRef);
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

	if(const auto enemySubs = GetGameInstance()->GetSubsystem<UEnemySubsystem>())
		enemySubs->OnEnemyDead.Broadcast(this);
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

void AEnemyController::SpawnPawn_Implementation(AEnemySpawnPoint* SpawnBox, int Type)
{
	//EnemyRef->OnPawnDeadSignature.AddDynamic(this, &AEnemyController::OnDead);

	//Possess(EnemyRef);
}
