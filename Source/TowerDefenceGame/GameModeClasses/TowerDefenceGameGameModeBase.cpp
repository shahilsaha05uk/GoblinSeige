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

		mGameSubsystem->OnPhaseLoad.AddDynamic(this, &ThisClass::OnPhaseLoad);
		mGameSubsystem->OnPhaseChangeComplete.AddDynamic(this, &ThisClass::OnPhaseComplete);
	}

	mWaveManager = GetWorld()->SpawnActor<AWaveManager>(WaveManagerClass);
	if(mWaveManager) mWaveManager->Init(this);
	
	mEnemyManager = GetWorld()->SpawnActor<AEnemyManager>(EnemyManagerClass);

	UpdateTargets();
	
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

void ATowerDefenceGameGameModeBase::OnPhaseComplete_Implementation()
{
	/* Check if all the phases are complete
	 * if yes:
	 *		check if the current wave == total wave AND all the enemies are killed
	 *			if so, Game Won,
	 *			else, Game Lost
	 */

}

void ATowerDefenceGameGameModeBase::OnWaveUpdated_Implementation(int Wave)
{
}

void ATowerDefenceGameGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	GetWorld()->GetFirstLocalPlayerFromController()->GetSubsystem<UResourceSubsystem>()->Add(mStartingResources);
	mPlayerController = NewPlayer;
}

bool ATowerDefenceGameGameModeBase::MakeDecision_Implementation()
{
	// Win Conditions
	/*
	 * if the current wave is == total wave
	 * if the enemies are all destroyed
	 */

	//if(mCurrentPhase >= mFinalPhase && )
	if(mCurrentPhase <= mFinalPhase &&
		mEnemyManager->TotalEnemyControllersAssigned &&
		mWaveManager->GetCurrentWave() >= mWaveManager->GetFinalWave())
	{
		// Game Won
		UE_LOG(LogTemp, Warning, TEXT("Game Won"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Lost"));
	}

	return false;
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
	
		if(mCurrentPhase > mFinalPhase)
		{
			const bool bWon = MakeDecision();
			mGameSubsystem->OnGameComplete.Broadcast(bWon);
		}
		else
		{
			UpdateTargets();
			mGameSubsystem->OnPhaseComplete.Broadcast(mCurrentPhase);
		}
	}
}

void ATowerDefenceGameGameModeBase::OnPhaseLoad_Implementation()
{
	mGameSubsystem->OnPhaseLoadedSuccessfully.AddDynamic(this, &ThisClass::OnPhaseLoadedSuccess);
}

void ATowerDefenceGameGameModeBase::OnPhaseLoadedSuccess_Implementation(int LoadedPhase)
{
	
}