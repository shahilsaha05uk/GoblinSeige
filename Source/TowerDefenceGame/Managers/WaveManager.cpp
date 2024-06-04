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
		mGameSubsystem->OnPhaseComplete.AddDynamic(this, &ThisClass::OnPhaseComplete);
		mGameSubsystem->OnPhaseLoadedSuccessfully.AddDynamic(this, &ThisClass::OnPhaseLoadedSuccessfully);
		mGameSubsystem->OnAllDead.AddDynamic(this, &ThisClass::WaveComplete);

		mGameSubsystem->OnGetCurrentWave.BindDynamic(this, &ThisClass::GetCurrentWave);
	}

	mTimerComp->OnFinishTimer.AddDynamic(this, &ThisClass::AWaveManager::OnTimerFinish);
	
	// get the latest timer and start the timer
	StartNextWave();
}

void AWaveManager::Init(ATowerDefenceGameGameModeBase* GameMode)
{
	mGameMode = GameMode;
}

#pragma region Phase Methods

void AWaveManager::OnPhaseLoadedSuccessfully(int Phase)
{
	if(FetchAndUpdateCountdownDetails(Phase2StartWave))
	{
		SetWave(Phase2StartWave);
		mTimerComp->StartTimer(mCountDownTimerDetails.CountDownTimer);
	}
}

void AWaveManager::OnPhaseComplete(int Phase)
{
	mTimerComp->ForceStopTimer();
}

#pragma endregion

#pragma region Timer Methods

bool AWaveManager::FetchAndUpdateCountdownDetails(int Wave)
{
	int waveToLookFor = (Wave == -1)? mCurrentWave : Wave;
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

void AWaveManager::WaveComplete_Implementation()
{
	mCurrentWave++;
	if(mCurrentWave >= mFinalWave)
	{
		mGameMode->MakeDecision();
	}
	else
	{
		if(mGameSubsystem)
		{
			mGameSubsystem->OnWaveUpdated.Broadcast(mCurrentWave);
		}
		
		StartNextWave();
	}
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
