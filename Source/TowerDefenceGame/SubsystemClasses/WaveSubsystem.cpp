// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveSubsystem.h"

void UWaveSubsystem::StartWave()
{
	OnWaveStarted.Broadcast(mCurrentWave);
}

void UWaveSubsystem::EndWave()
{
	if(mCurrentWave >= mFinalWave) return;
	mCurrentWave++;
	OnWaveComplete.Broadcast(mCurrentWave);
}
