// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGame/TowerDefenceGameGameModeBase.h"
#include "TowerDefenceGame/ManagerClasses/WaveManager.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
	
	gameMode = Cast<ATowerDefenceGameGameModeBase>(GetWorld()->GetAuthGameMode());

	if(gameMode)
	{
		if(class AWaveManager* waveManager = gameMode->GetWaveManager()) waveManager->OnWaveStartSignature.AddDynamic(this, &UPlayerHUD::OnWaveStart);
	}
}

void UPlayerHUD::OnWaveStart_Implementation()
{
	
}
