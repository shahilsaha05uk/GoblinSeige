// Fill out your copyright notice in the Description page of Project Settings.


#include "PhaseManager.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGame/GameModeClasses/TowerDefenceGameGameModeBase.h"
#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"

void APhaseManager::BeginPlay()
{
	Super::BeginPlay();
	mGameSubsystem = GetGameInstance()->GetSubsystem<UGameSubsystem>();

	LoadPhase();
}

void APhaseManager::Init_Implementation(ATowerDefenceGameGameModeBase* GameMode)
{
	mGameMode = GameMode;
}

bool APhaseManager::LoadPhase_Implementation()
{
	FLatentActionInfo info;
	info.CallbackTarget = this;
	info.Linkage = 0;

	// unloading the last phase
	if(mPhaseDetails.Contains(mCurrentPhase))
	{
		auto const PhaseDetails = mPhaseDetails[mCurrentPhase];
		UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(), PhaseDetails.LevelMap, info, true);
	}

	// increment the phase count
	mCurrentPhase++;
	
	// loading the next phase
	if(mPhaseDetails.Contains(mCurrentPhase))
	{
		info.ExecutionFunction = FName("OnPhaseLoaded");
		mCurrentPhaseDetails = mPhaseDetails[mCurrentPhase];
		UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(), mCurrentPhaseDetails.LevelMap, true, true, info);
		return true;
	}

	return false;
}
void APhaseManager::OnPhaseLoaded_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Loading Finish"));
	UpdateTargets();
	mGameSubsystem->OnPhaseReadyToPlay.Broadcast(mCurrentPhase, mCurrentPhaseDetails);
}

void APhaseManager::TargetDestroyed_Implementation()
{
	if(mGameSubsystem) mGameSubsystem->OnTargetDestroyed.Broadcast();

	if(mTotalTargetsToDestroy <= 0)
	{
		OnNoTargetsLeft.Broadcast();

		if(!LoadPhase())
		{
			mGameMode->MakeDecision();
		}
		else
		{
			mGameSubsystem->OnPhaseComplete.Broadcast(mCurrentPhase);
		}
	}
}

void APhaseManager::UpdatePhase_Implementation()
{
}

void APhaseManager::UpdateTargets_Implementation()
{
	if(mPhaseDetails.Contains(mCurrentPhase))
	{
		mTotalTargetsToDestroy = mPhaseDetails[mCurrentPhase].TargetsToDestroy;
	}
}
