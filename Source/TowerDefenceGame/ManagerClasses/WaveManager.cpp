// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

#include "TowerDefenceGame/EnumClass.h"

// Sets default values
AWaveManager::AWaveManager()
{

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
	mCurrentWave++;
}


