// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenceGameGameModeBase.h"
#include "TowerDefenceGame/SubsystemClasses/EnemySubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/GameDecisionSubsytem.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/WaveSubsystem.h"

void ATowerDefenceGameGameModeBase::BeginPlay()
{
	if(auto waveSubsystem = GetGameInstance()->GetSubsystem<UWaveSubsystem>())
	{
		waveSubsystem->OnWaveStarted.AddDynamic(this, &ThisClass::OnWaveStart);
		waveSubsystem->OnWaveComplete.AddDynamic(this, &ThisClass::OnWaveComplete);
	}
	if(auto gameDecision = GetGameInstance()->GetSubsystem<UGameDecisionSubsytem>())
	{
		gameDecision->OnGameDecisionMade.AddDynamic(this, &ThisClass::GameOver);
	}
	Super::BeginPlay();
}

void ATowerDefenceGameGameModeBase::GameOver_Implementation()
{
	if(auto enemySubsystem = GetGameInstance()->GetSubsystem<UEnemySubsystem>())
	{
		enemySubsystem->FlushEverything();
	}
}

void ATowerDefenceGameGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	GetGameInstance()->GetSubsystem<UResourceSubsystem>()->Add(mStartingResources);

	mPlayerController = NewPlayer;
}

void ATowerDefenceGameGameModeBase::OnWaveStart_Implementation(int Wave)
{
	if(auto enemySubsystem = GetGameInstance()->GetSubsystem<UEnemySubsystem>())
	{
		enemySubsystem->PrepareForWave(Wave);
	}
}

void ATowerDefenceGameGameModeBase::OnWaveComplete_Implementation(int WaveNumber)
{
	if(auto waveSubsystem = GetGameInstance()->GetSubsystem<UWaveSubsystem>())
	{
		if(WaveNumber >= waveSubsystem->GetFinalWave())
		{
			GetGameInstance()->GetSubsystem<UGameDecisionSubsytem>()->Trigger_OnGameDecisionMade();
		}
	}
}