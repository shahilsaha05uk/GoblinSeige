// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenceGameGameModeBase.h"

int ATowerDefenceGameGameModeBase::GetWave(ELevel level)
{
	switch (level) { case NO_LEVEL: return -1; break;
	case CURRENT_LEVEL: return mCurrentWave; break;
	case FINAL_LEVEL: return mFinalWave; break;
	case INITIAL_LEVEL: return mInitialWave; break;
	default: return -1;
	}
}

void ATowerDefenceGameGameModeBase::UpdateWave()
{
	mCurrentWave++;
}
