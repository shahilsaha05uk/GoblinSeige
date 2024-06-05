// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/InterfaceClasses/EnemyInterface.h"
#include "TowerDefenceGame/Managers/EnemyManager.h"
#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	mGameSubsytem = GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if(mGameSubsytem)
	{
		mGameSubsytem->OnPhaseComplete.AddDynamic(this, &ThisClass::OnPhaseComplete);
		mGameSubsytem->OnGameComplete.AddDynamic(this, &ThisClass::OnGameComplete);
	}

}

void AEnemyController::OnUnPossess()
{
	Super::OnUnPossess();

	mGameSubsytem->OnEnemyDie.Broadcast(this);
}

void AEnemyController::SpawnPawn_Implementation(FVector SpawnPoint, int Type)
{

}

void AEnemyController::EnemyMove_Implementation(ASpline* Spline)
{
	APawn* pawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UEnemyInterface::StaticClass()))
	{
		IEnemyInterface::Execute_IA_FollowTheSpline(pawn, Spline);
	}
}

void AEnemyController::EnemyAttack_Implementation()
{
	APawn* pawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UEnemyInterface::StaticClass()))
	{
		IEnemyInterface::Execute_IA_EnemyAttack(pawn);
	}
}

void AEnemyController::OnPhaseComplete_Implementation(int Phase)
{
	UnPossess();
	Destroy();
}

void AEnemyController::OnGameComplete_Implementation(bool bWon)
{
	UnPossess();
	Destroy();
}
