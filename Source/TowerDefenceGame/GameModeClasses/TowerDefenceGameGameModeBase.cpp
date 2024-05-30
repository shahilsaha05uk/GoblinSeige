// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenceGameGameModeBase.h"
#include <TowerDefenceGame/SubsystemClasses/GameSubsystem.h>
#include "TowerDefenceGame/Managers/EnemyManager.h"
#include "TowerDefenceGame/Managers/WaveManager.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"

void ATowerDefenceGameGameModeBase::BeginPlay()
{
	if(const auto gameSubsystem = GetGameInstance()->GetSubsystem<UGameSubsystem>())
	{
		gameSubsystem->OnGameDecisionMade.AddDynamic(this, &ThisClass::GameOver);
	}

	mWaveManager = GetWorld()->SpawnActor<AWaveManager>(WaveManagerClass);
	mEnemyManager = GetWorld()->SpawnActor<AEnemyManager>(EnemyManagerClass);
	
	Super::BeginPlay();
}

void ATowerDefenceGameGameModeBase::GameOver_Implementation()
{
}

void ATowerDefenceGameGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	GetGameInstance()->GetSubsystem<UResourceSubsystem>()->Add(mStartingResources);
	mPlayerController = NewPlayer;
}