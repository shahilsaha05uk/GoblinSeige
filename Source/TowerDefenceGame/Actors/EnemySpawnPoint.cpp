// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnPoint.h"

#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"


void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	mGameSubsystem = GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if(mGameSubsystem)
	{
		mGameSubsystem->OnPhaseComplete.AddDynamic(this, &ThisClass::OnPhaseComplete);
		mGameSubsystem->OnPhaseLoadedSuccessfully.AddDynamic(this, &ThisClass::OnPhaseLoaded);
		//mGameSubsystem->OnPrepareForPhaseChange.AddDynamic(this, &ThisClass::OnPrepareForPhaseChange);

		mGameSubsystem->RegisterSpawnPoint(this);
	}
}


void AEnemySpawnPoint::OnPhaseComplete(int Phase)
{
	if(mGameSubsystem) mGameSubsystem->DeRegisterSpawnPoint(this);
}

void AEnemySpawnPoint::OnPhaseLoaded(int LoadedPhase)
{
	if(mGameSubsystem) mGameSubsystem->RegisterSpawnPoint(this);
}

FVector AEnemySpawnPoint::GetRandomPointInsideTheSpawnArea_Implementation()
{
	return FVector(0, 0, 0);
}

