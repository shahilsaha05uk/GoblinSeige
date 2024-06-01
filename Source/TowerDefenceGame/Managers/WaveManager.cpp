#include "WaveManager.h"

#include "TowerDefenceGame/SubsystemClasses/ClockSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/WaveSubsystem.h"

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
	mWaveSubsystem = GetGameInstance()->GetSubsystem<UWaveSubsystem>();
	if(mWaveSubsystem)
	{
		mWaveSubsystem->Init(mInitialWave, mFinalWave);
		mWaveSubsystem->OnWaveUpdated.AddDynamic(this, &ThisClass::OnWaveComplete);
	}

	if(const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
	{
		if(auto const ClockSubsystem = LocalPlayer->GetSubsystem<UClockSubsystem>())
		{
			ClockSubsystem->FinishTimer.AddDynamic(this, &ThisClass::OnTimerFinish);
		}
	}
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