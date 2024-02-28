#include "WaveManager.h"
#include "TowerDefenceGame/GameModeClasses/TowerDefenceGameGameModeBase.h"
#include "TowerDefenceGame/InterfaceClasses/GameModeInterface.h"


void AWaveManager::Init_Implementation(ATowerDefenceGameGameModeBase* gameMode)
{
	mCurrentWave = mInitialWave;
	mGameMode = gameMode;
}

void AWaveManager::StartWave_Implementation()
{
	OnWaveStartSignature.Broadcast();
	IGameModeInterface::Execute_GetEnemyManager(mGameMode)->PrepareForWave(mCurrentWave);
}

void AWaveManager::EndWave_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("DECLARE WAVE END!!!"));

	UpdateWave();

	mGameMode->OnWaveCompleteSignature.Broadcast(mCurrentWave);
}

int AWaveManager::GetWave(EWave level)
{
	switch (level) { case NO_WAVE: return -1; break;
	case CURRENT_WAVE: return mCurrentWave; break;
	case FINAL_WAVE: return mFinalWave; break;
	case INITIAL_WAVE: return mInitialWave; break;
	default: return -1;
	}
}

void AWaveManager::UpdateWave()
{
	if(mCurrentWave >= mFinalWave) return;
	mCurrentWave++;
}
