// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGame/EnumClass.h"
#include "TowerDefenceGame/TowerDefenceGameGameModeBase.h"



void AWaveManager::Init_Implementation(ATowerDefenceGameGameModeBase* gameMode)
{
	mCurrentWave = mInitialWave;
	mGameMode = gameMode;
}

void AWaveManager::StartWave_Implementation()
{
	mGameMode->GetEnemyManager()->PrepareForWave(mCurrentWave);
}

void AWaveManager::EndWave_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("DECLARE WAVE END!!!"));

	UpdateWave();

	mGameMode->OnWaveCompleteSignature.Broadcast(mCurrentWave);
}

int AWaveManager::GetWave(ELevel level)
{
	switch (level) { case NO_LEVEL: return -1; break;
	case CURRENT_LEVEL: return mCurrentWave; break;
	case FINAL_LEVEL: return mFinalWave; break;
	case INITIAL_LEVEL: return mInitialWave; break;
	default: return -1;
	}
}

void AWaveManager::UpdateWave()
{
	if(mCurrentWave >= mFinalWave) return;
	mCurrentWave++;
}



