// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

#include "TowerDefenceGame/BaseClasses/BaseEnemy.h"
#include "Navigation/PathFollowingComponent.h"
#include "TowerDefenceGame/SubsystemClasses/EnemySubsystem.h"

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	InPawn->OnDestroyed.AddDynamic(this, &ThisClass::OnPawnDestroyed);
	RunBehaviorTree(BehaviorTreeRef);
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

void AEnemyController::OnPawnDestroyed(AActor* DestroyedActor)
{
	if(APawn* p = GetPawn())
	{
		p->Destroy();
		UnPossess();

		if(const auto enemySubs = GetGameInstance()->GetSubsystem<UEnemySubsystem>())
		{
			enemySubs->OnEnemyDead.Broadcast(this);
		}
	}
}

