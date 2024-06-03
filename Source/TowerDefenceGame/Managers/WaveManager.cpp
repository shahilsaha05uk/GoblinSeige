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
		GameSubs->OnPhaseChange.AddDynamic(this, &ThisClass::OnPhaseChange);
	}

	if(const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
	{
		if(auto const ClockSubsystem = LocalPlayer->GetSubsystem<UClockSubsystem>())
		{
			ClockSubsystem->FinishTimer.AddDynamic(this, &ThisClass::OnTimerFinish);
		}
	}

	mTimerComp->StartTimer();
}

void AWaveManager::OnWaveComplete_Implementation(int WaveNumber)
{
	if(const auto waveSubsystem = GetGameInstance()->GetSubsystem<UWaveSubsystem>())
	{
		if(WaveNumber >= waveSubsystem->GetFinalWave())
		{
			GetGameInstance()->GetSubsystem<UGameSubsystem>()->OnGameDecisionMade.Broadcast();
		}
	}
}

void AWaveManager::OnTimerFinish()
{
	mWaveSubsystem->StartWave();
}

void AWaveManager::OnPhaseChange()
{
	mTimerComp->StartTimer();
}
