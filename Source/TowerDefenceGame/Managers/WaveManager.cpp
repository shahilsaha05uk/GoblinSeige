#include "WaveManager.h"

#include "TowerDefenceGame/ActorComponentClasses/TimerComponent.h"
#include "TowerDefenceGame/GameModeClasses/TowerDefenceGameGameModeBase.h"
#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"

AWaveManager::AWaveManager()
{
	mTimerComp = CreateDefaultSubobject<UTimerComponent>("TimerComponent");
}

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	mGameSubsystem = GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if(mGameSubsystem)
	{
		mGameSubsystem->OnGameComplete.AddDynamic(this, &ThisClass::OnGameComplete);
		mGameSubsystem->OnPhaseComplete.AddDynamic(this, &ThisClass::OnPhaseComplete);
		mGameSubsystem->OnPhaseReadyToPlay.AddDynamic(this, &ThisClass::OnPhaseReadyToPlay);

		mGameSubsystem->OnAllDead.AddDynamic(this, &ThisClass::OnAllEnemiesDead);
	}

	mTimerComp->OnFinishTimer.AddDynamic(this, &ThisClass::AWaveManager::OnTimerFinish);
	
	// get the latest timer and start the timer
	//StartNextWave();
}


void AWaveManager::Init(ATowerDefenceGameGameModeBase* GameMode)
{
	mGameMode = GameMode;
}

void AWaveManager::OnAllEnemiesDead_Implementation()
{
	AddWaveCount();
	StartNextWave();
}

#pragma region Phase Methods

void AWaveManager::RevertWave(int PhaseLostCount)
{
	// TODO: find a scalable solution for this
	if(FetchAndUpdateCountdownDetails(Phase2StartWave))
	{
		SetWave(Phase2StartWave);
	}
}

void AWaveManager::OnPhaseReadyToPlay(int PhaseCount)
{
	const FString str = "Wave Countdown Started"; 
	mGameSubsystem->OnFeedbackEnabled.Broadcast(Feed_Success, str);
	
	StartNextWave();
}

void AWaveManager::OnPhaseComplete(int Phase)
{
	mTimerComp->StopAndResetTimer();
}

#pragma endregion

#pragma region Timer Methods

bool AWaveManager::FetchAndUpdateCountdownDetails(int Wave)
{
	const int waveToLookFor = (Wave == -1)? mCurrentWave : Wave;
	if(mDACountDownTimer)
	{
		if(mDACountDownTimer->GetCountDownDetails(waveToLookFor, mCountDownTimerDetails))
		{
			return true;
		}
	}
	return false;
}

void AWaveManager::OnTimerFinish()
{
	mGameSubsystem->OnWaveStarted.Broadcast(mCurrentWave);
}

#pragma endregion

#pragma region Wave Management

void AWaveManager::SetWave(int Wave)
{
	mCurrentWave = Wave;
	mGameSubsystem->OnWaveUpdated.Broadcast(mCurrentWave);
}

void AWaveManager::AddWaveCount()
{
	mCurrentWave++;
	mGameSubsystem->OnWaveUpdated.Broadcast(mCurrentWave);
}

void AWaveManager::StartNextWave_Implementation()
{
	if(mCurrentWave > mCountDownTimerDetails.MaxLevel)
	{
		if(FetchAndUpdateCountdownDetails())
		{
			mTimerComp->StartTimer(mCountDownTimerDetails.CountDownTimer);
		}
	}
	else
	{
		mTimerComp->StartTimer(mCountDownTimerDetails.CountDownTimer);
	}
}

#pragma endregion

void AWaveManager::OnGameComplete(bool bWon)
{
	mTimerComp->StopAndResetTimer();
}