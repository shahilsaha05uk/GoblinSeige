// Fill out your copyright notice in the Description page of Project Settings.


#include "PhaseManager.h"

#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"
#include "Streaming/LevelStreamingDelegates.h"
#include "TowerDefenceGame/GameModeClasses/TowerDefenceGameGameModeBase.h"
#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"

void APhaseManager::Init_Implementation(ATowerDefenceGameGameModeBase* GameMode)
{
	mGameMode = GameMode;
	mGameSubsystem = GetGameInstance()->GetSubsystem<UGameSubsystem>();

	if(mGameSubsystem)
	{
		mGameSubsystem->OnTargetDestroyed.AddDynamic(this, &ThisClass::TargetDestroyed);
	}

	LoadPhase();
}

bool APhaseManager::LoadPhase_Implementation()
{
	// unloading the last phase
	if(mPhaseDetails.Contains(mCurrentPhase))
	{
		FLatentActionInfo unloadInfo;
		unloadInfo.CallbackTarget = this;
		unloadInfo.ExecutionFunction = FName("OnPhaseUnloaded");
		unloadInfo.Linkage = 0;
		unloadInfo.UUID = __LINE__; // Ensure uniqueness
		auto const PhaseDetails = mPhaseDetails[mCurrentPhase];
		UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(), PhaseDetails.LevelMap, unloadInfo, true);
	}

	// increment the phase count
	mCurrentPhase++;
	
	// loading the next phase
	if(mPhaseDetails.Contains(mCurrentPhase))
	{
		FLatentActionInfo loadInfo;
		loadInfo.CallbackTarget = this;
		loadInfo.ExecutionFunction = FName("OnPhaseLoaded");
		loadInfo.Linkage = 0;
		loadInfo.UUID = __LINE__; // Ensure uniqueness
		mCurrentPhaseDetails = mPhaseDetails[mCurrentPhase];

		// gets the streaming level
		const FSoftObjectPath LevelPath = mCurrentPhaseDetails.LevelMap.ToSoftObjectPath();
		const FString PackageName = LevelPath.GetLongPackageName();
		const auto levelStream = UGameplayStatics::GetStreamingLevel(GetWorld(), FName(*PackageName));

		// Load the stream level
		UGameplayStatics::LoadStreamLevel(GetWorld(), FName(*PackageName), true, true, loadInfo);

		// called when the level is loaded
		if(levelStream)
		{
			levelStream->OnLevelShown.AddDynamic(this, &ThisClass::OnPhaseLoaded);
		}

		return true;
	}
	
	return false;
}

void APhaseManager::OnPhaseLoaded_Implementation()
{
	UpdateTargets();

	if(mGameSubsystem)
		mGameSubsystem->OnPhaseLoadedSuccessfully.Broadcast(mCurrentPhase, mCurrentPhaseDetails);
}

void APhaseManager::TargetDestroyed_Implementation()
{
	mTotalTargetsToDestroy--;
	
	if(mTotalTargetsToDestroy <= 0)
	{
		OnNoTargetsLeft.Broadcast();

		if(!LoadPhase())
		{
			mGameSubsystem->OnGameComplete.Broadcast(false);
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
