#include "WaveManager.h"

#include "TowerDefenceGame/ActorComponentClasses/TimerComponent.h"
#include "TowerDefenceGame/SubsystemClasses/ClockSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/WaveSubsystem.h"

AWaveManager::AWaveManager()
{
	mTimerComp = CreateDefaultSubobject<UTimerComponent>("TimerComponent");
}

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
	mWaveSubsystem = GetGameInstance()->GetSubsystem<UWaveSubsystem>();
	if(mWaveSubsystem)
	{
		mWaveSubsystem->Init(mInitialWave, mFinalWave);
		mWaveSubsystem->OnWaveUpdated.AddDynamic(this, &ThisClass::OnWaveComplete);
	}

	if(const auto GameSubs = GetGameInstance()->GetSubsystem<UGameSubsystem>())
	{
		GameSubs->OnPhaseChangeComplete.AddDynamic(this, &ThisClass::OnPhaseChangeComplete);
		GameSubs->OnPrepareForPhaseChange.AddDynamic(this, &ThisClass::OnPrepareForPhaseChange);
	}

	if(const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
	{
		if(auto const ClockSubsystem = LocalPlayer->GetSubsystem<UClockSubsystem>())
		{
			ClockSubsystem->FinishTimer.AddDynamic(this, &ThisClass::OnTimerFinish);
		}
	}

	// get the latest timer and start the timer
	FetchAndUpdateCountdownDetails();
	mTimerComp->StartTimer(mCountDownTimerDetails.CountDownTimer);
}

void AWaveManager::OnWaveComplete_Implementation(int WaveNumber)
{
	if(mWaveSubsystem->GetCurrentWave() >= mWaveSubsystem->GetFinalWave())
	{
		GetGameInstance()->GetSubsystem<UGameSubsystem>()->OnGameDecisionMade.Broadcast();
	}

	if(WaveNumber > mCountDownTimerDetails.MaxLevel)
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

#pragma region Phase Methods

void AWaveManager::OnPhaseChangeComplete()
{
	if(FetchAndUpdateCountdownDetails(Phase2StartWave))
	{
		mWaveSubsystem->SetWave(Phase2StartWave);
		mTimerComp->StartTimer(mCountDownTimerDetails.CountDownTimer);
	}
}

void AWaveManager::OnPrepareForPhaseChange()
{
	mTimerComp->ForceStopTimer();
}

#pragma endregion

#pragma region Timer Methods

bool AWaveManager::FetchAndUpdateCountdownDetails(int Wave)
{
	int waveToLookFor = (Wave == -1)? mWaveSubsystem->GetCurrentWave() : Wave;
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
	mWaveSubsystem->StartWave();
}

#pragma endregion
