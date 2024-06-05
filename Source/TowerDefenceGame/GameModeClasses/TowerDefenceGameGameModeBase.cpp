// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenceGameGameModeBase.h"
#include <TowerDefenceGame/SubsystemClasses/GameSubsystem.h>
#include "TowerDefenceGame/Managers/EnemyManager.h"
#include "TowerDefenceGame/Managers/WaveManager.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"

void ATowerDefenceGameGameModeBase::BeginPlay()
{
	mGameSubsystem = GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if(mGameSubsystem)
	{
		mGameSubsystem->OnGameDecisionMade.AddDynamic(this, &ThisClass::GameOver);
		mGameSubsystem->OnTargetDestroyed.AddDynamic(this, &ThisClass::OnTargetDestroyed);
		mGameSubsystem->OnWaveUpdated.AddDynamic(this, &ThisClass::OnWaveUpdated);
	}

	mWaveManager = GetWorld()->SpawnActor<AWaveManager>(WaveManagerClass);
	if(mWaveManager) mWaveManager->Init(this);
	
	mEnemyManager = GetWorld()->SpawnActor<AEnemyManager>(EnemyManagerClass);

	Super::BeginPlay();
}

void ATowerDefenceGameGameModeBase::UpdateTargets_Implementation()
{
	if(mPhaseTargetBreachMap.Contains(mCurrentPhase))
	{
		mTotalTargetsToDestroy = mPhaseTargetBreachMap[mCurrentPhase];
	}
}


void ATowerDefenceGameGameModeBase::GameOver_Implementation()
{
}

void ATowerDefenceGameGameModeBase::OnWaveUpdated_Implementation(int Wave)
{
	if(Wave >= mWaveManager->GetFinalWave())
	{
		mGameSubsystem->OnGameComplete.Broadcast(true);
	}
}

void ATowerDefenceGameGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	GetWorld()->GetFirstLocalPlayerFromController()->GetSubsystem<UResourceSubsystem>()->Add(mStartingResources);
	mPlayerController = NewPlayer;
}

bool ATowerDefenceGameGameModeBase::MakeDecision_Implementation()
{
	if(mWaveManager->GetCurrentWave() >= mWaveManager->GetFinalWave())
	{
		mGameSubsystem->OnGameComplete.Broadcast(true);
		return true;
	}
	mGameSubsystem->OnGameComplete.Broadcast(false);
	return false;
}


void ATowerDefenceGameGameModeBase::OnPhaseLoad_Implementation()
{
	UpdateTargets();
}

void ATowerDefenceGameGameModeBase::LoadPhase_Implementation()
{
}

void ATowerDefenceGameGameModeBase::OnTargetDestroyed_Implementation()
{
	// check how many targets are expected to be destroyed before moving to the next phase
	mTotalTargetsToDestroy--;

	const FString str = "You failed to defend the doors"; 
	mGameSubsystem->OnFeedbackEnabled.Broadcast(Feed_Failed, str);
	
	// if the total destroyed targets is 0, than the phase should be complete
	if(mTotalTargetsToDestroy <=0)
	{
		mCurrentPhase++;

		if(mCurrentPhase > mFinalPhase) mCurrentPhase = -1;

		mGameSubsystem->OnPhaseComplete.Broadcast(mCurrentPhase);
		if(mCurrentPhase == -1)
		{
			MakeDecision();
		}
		else
		{
			mWaveManager->RevertWave(mCurrentPhase);
			UpdateTargets();
		}
	}
} 