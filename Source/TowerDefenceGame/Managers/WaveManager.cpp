#include "WaveManager.h"
#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/WaveSubsystem.h"

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
	mWaveSubsystem = GetGameInstance()->GetSubsystem<UWaveSubsystem>();
	if(mWaveSubsystem)
	{
		mWaveSubsystem->Init(mInitialWave, mFinalWave);
		mWaveSubsystem->OnWaveComplete.AddDynamic(this, &ThisClass::OnWaveComplete);
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
