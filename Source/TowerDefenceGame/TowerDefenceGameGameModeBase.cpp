// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenceGameGameModeBase.h"

#include "ManagerClasses/WaveManager.h"


ATowerDefenceGameGameModeBase::ATowerDefenceGameGameModeBase()
{
	OnWaveCompleteSignature.AddDynamic(this, &ATowerDefenceGameGameModeBase::OnWaveComplete);
	OnGameOverSignature.AddDynamic(this, &ATowerDefenceGameGameModeBase::OnGameOver);
}

void ATowerDefenceGameGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	mPlayerController = NewPlayer;
}

void ATowerDefenceGameGameModeBase::OnWaveComplete_Implementation(int WaveNumber)
{
	if(mWaveManager->GetWave(CURRENT_LEVEL) >= mWaveManager->GetWave(FINAL_LEVEL))
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Complete!!"));

		//TODO: Game is Complete!!
		OnGameCompleteSignature.Broadcast();
	}
}

void ATowerDefenceGameGameModeBase::OnGameOver_Implementation()
{
	
}