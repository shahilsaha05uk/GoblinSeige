// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnPoint.h"

#include "TowerDefenceGame/SubsystemClasses/EnemySubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"


void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	if(const auto GameSubs = GetGameInstance()->GetSubsystem<UGameSubsystem>())
	{
		GameSubs->OnPhaseChangeComplete.AddDynamic(this, &ThisClass::OnPhaseChangeComplete);
		GameSubs->OnPrepareForPhaseChange.AddDynamic(this, &ThisClass::OnPrepareForPhaseChange);
	}

	mEnemySubsystem = GetGameInstance()->GetSubsystem<UEnemySubsystem>();
	if(mEnemySubsystem) mEnemySubsystem->RegisterSpawnPoint(this);
}

void AEnemySpawnPoint::OnPrepareForPhaseChange()
{
	if(mEnemySubsystem) mEnemySubsystem->DeRegisterSpawnPoint(this);
}

void AEnemySpawnPoint::OnPhaseChangeComplete()
{
	if(mEnemySubsystem) mEnemySubsystem->RegisterSpawnPoint(this);
}

FVector AEnemySpawnPoint::GetRandomPointInsideTheSpawnArea_Implementation()
{
	return FVector(0, 0, 0);
}

