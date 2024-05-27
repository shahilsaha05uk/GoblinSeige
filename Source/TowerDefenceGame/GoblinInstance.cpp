// Fill out your copyright notice in the Description page of Project Settings.


#include "GoblinInstance.h"

#include "SubsystemClasses/EnemySubsystem.h"
#include "SubsystemClasses/WaveSubsystem.h"

void UGoblinInstance::Init()
{
	Super::Init();

	if(const auto enemySubs = GetSubsystem<UEnemySubsystem>())
	{
		enemySubs->InitSub(mEnemyControllerClass);
	}
	if(const auto waveSubsystem = GetSubsystem<UWaveSubsystem>())
	{
		waveSubsystem->Init(mInitialWave, mFinalWave);
	}
}

void UGoblinInstance::TravelToMap_Implementation(ELevelToTravel LevelToTravel)
{
	
}
