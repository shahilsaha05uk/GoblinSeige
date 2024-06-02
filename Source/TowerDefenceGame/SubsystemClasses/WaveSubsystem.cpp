// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveSubsystem.h"

void UWaveSubsystem::Init(int initialWave, int finalWave)
{
	mInitialWave = initialWave;
	mFinalWave = finalWave;
	mCurrentWave = mInitialWave;
	OnWaveUpdated.Broadcast(mCurrentWave);
}

void UWaveSubsystem::StartWave()
{
	OnWaveStarted.Broadcast(mCurrentWave);
}

void UWaveSubsystem::EndWave()
{
	if(mCurrentWave >= mFinalWave) return;
	mCurrentWave++;
	OnWaveUpdated.Broadcast(mCurrentWave);
}
