#include "WaveManager.h"
#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/WaveSubsystem.h"

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
	mWaveSubsystem = GetGameInstance()->GetSubsystem<UWaveSubsystem>();
	if(mWaveSubsystem)
	{
		mWaveSubsystem->OnWaveStarted.AddDynamic(this, &ThisClass::OnWaveStart);
		mWaveSubsystem->OnWaveComplete.AddDynamic(this, &ThisClass::OnWaveComplete);
	}
}
void AWaveManager::OnWaveStart_Implementation(int Wave)
{
	mWaveSubsystem->OnWaveStarted.Broadcast(Wave);
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
