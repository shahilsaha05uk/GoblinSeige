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
		mGameSubsystem->OnTargetDestroyed.AddDynamic(this, &ThisClass::OnTargetDestroyed);
		mGameSubsystem->OnWaveUpdated.AddDynamic(this, &ThisClass::OnWaveUpdated);
	}

	mWaveManager = GetWorld()->SpawnActor<AWaveManager>(WaveManagerClass);
	if(mWaveManager) mWaveManager->Init(this);
	
	mEnemyManager = GetWorld()->SpawnActor<AEnemyManager>(EnemyManagerClass);

	Super::BeginPlay();
}
void ATowerDefenceGameGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	GetWorld()->GetFirstLocalPlayerFromController()->GetSubsystem<UResourceSubsystem>()->Add(mStartingResources);
	mPlayerController = NewPlayer;
}

void ATowerDefenceGameGameModeBase::UpdateTargets_Implementation()
{
	if(mPhaseDetails.Contains(mCurrentPhase))
	{
		mTotalTargetsToDestroy = mPhaseDetails[mCurrentPhase].TargetsToDestroy;
	}
}


void ATowerDefenceGameGameModeBase::OnWaveUpdated_Implementation(int Wave)
{
	MakeWaveDecision();
}

void ATowerDefenceGameGameModeBase::OnTargetDestroyed_Implementation()
{
	// check how many targets are expected to be destroyed before moving to the next phase
	mTotalTargetsToDestroy--;

	if(mTotalTargetsToDestroy <=0)	MakePhaseDecision();
}

void ATowerDefenceGameGameModeBase::MakeWaveDecision_Implementation()
{
	if(HasCompletedAllTheWaves())	// if completed all the waves, than game won
	{
		mGameSubsystem->OnGameComplete.Broadcast(true);
	}
}

void ATowerDefenceGameGameModeBase::MakePhaseDecision_Implementation()
{
	// if the waves arent completed
	if(HasDestroyedAllTheTargets())
	{
		mCurrentPhase++;
		
		if(HasPhasesLeft())	// if there is any phases left than, load that
		{
			if(mPhaseDetails.Contains(mCurrentPhase))
			{
				mGameSubsystem->OnPhaseComplete.Broadcast(mCurrentPhase);	// notify that the phase is complete
				
				UpdatePhase();	// update the phase
				
				OnPhaseLoad();	// load the next phase
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Phase Details doesnt have any details regarding Phase %d"), mCurrentPhase);
			}
		}
		else	
		{
			//mGameSubsystem->OnPhaseComplete.Broadcast(-1);	// notify that the phase is complete

			// Send Feedback that they failed to defend the doors
			const FString str = "You failed to defend the doors"; 
			mGameSubsystem->OnFeedbackEnabled.Broadcast(Feed_Failed, str);
			
			//else declare game over
			mGameSubsystem->OnGameComplete.Broadcast(false);
		}
	}
	else
	{
		// if all the targets arent destroyed, than move to the next wave
		MakeWaveDecision();
	}
}

void ATowerDefenceGameGameModeBase::UpdatePhase_Implementation()
{
	// return back to a certain wave
	mWaveManager->RevertWave(mCurrentPhase);

	// update the target count
	UpdateTargets();
}

void ATowerDefenceGameGameModeBase::OnPhaseLoad_Implementation()
{
	UpdateTargets();
}

void ATowerDefenceGameGameModeBase::LoadPhase_Implementation()
{
}

#pragma region Decision Making Helpers

bool ATowerDefenceGameGameModeBase::HasCompletedAllTheWaves(int Wave) const
{
	const int waveCount = (Wave == -1)? mWaveManager->GetCurrentWave() : Wave;

	return waveCount >= mWaveManager->GetFinalWave();
}

bool ATowerDefenceGameGameModeBase::HasDestroyedAllTheTargets() const
{
	return (mTotalTargetsToDestroy == 0);
}

bool ATowerDefenceGameGameModeBase::HasPhasesLeft() const
{
	return (mCurrentPhase <= mFinalPhase);
}

#pragma endregion
