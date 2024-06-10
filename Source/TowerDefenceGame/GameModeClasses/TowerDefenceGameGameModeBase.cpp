// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenceGameGameModeBase.h"
#include <TowerDefenceGame/SubsystemClasses/GameSubsystem.h>
#include "TowerDefenceGame/Managers/EnemyManager.h"
#include "TowerDefenceGame/Managers/PhaseManager.h"
#include "TowerDefenceGame/Managers/WaveManager.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"

void ATowerDefenceGameGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	mGameSubsystem = GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if(mGameSubsystem)
	{
		mGameSubsystem->OnWaveUpdated.AddDynamic(this, &ThisClass::OnWaveUpdated);
	}

	mWaveManager = GetWorld()->SpawnActor<AWaveManager>(WaveManagerClass);
	if(mWaveManager) mWaveManager->Init(this);
	
	mEnemyManager = GetWorld()->SpawnActor<AEnemyManager>(EnemyManagerClass);

	mPhaseManager = GetWorld()->SpawnActor<APhaseManager>(PhaseManagerClass);
	if(mPhaseManager)
		mPhaseManager->Init(this);
}

void ATowerDefenceGameGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	mPlayerController = NewPlayer;
}


void ATowerDefenceGameGameModeBase::OnWaveUpdated_Implementation(int Wave)
{

}

void ATowerDefenceGameGameModeBase::ReadyToPlay_Implementation()
{
	mWaveManager->StartNextWave();
}

