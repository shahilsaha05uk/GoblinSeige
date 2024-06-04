// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/InterfaceClasses/EnemyInterface.h"
#include "TowerDefenceGame/Managers/EnemyManager.h"
#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	if(auto const GameSubs = GetGameInstance()->GetSubsystem<UGameSubsystem>())
		GameSubs->OnPhaseComplete.AddDynamic(this, &ThisClass::OnPhaseComplete);

}
void AEnemyController::InitController_Implementation(AEnemyManager* EnemyManager)
{
	if(EnemyManager)
	{
		mEnemyManager = EnemyManager;
	}
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AEnemyController::OnUnPossess()
{
	Super::OnUnPossess();
	if(APawn* pawn = GetPawn())
	{
		UnPossess();
		pawn->Destroy();
	}
}

void AEnemyController::SpawnPawn_Implementation(AEnemySpawnPoint* SpawnBox, int Type)
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
