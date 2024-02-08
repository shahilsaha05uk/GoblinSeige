// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGame/TowerDefenceGameGameModeBase.h"
#include "TowerDefenceGame/ManagerClasses/WaveManager.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
	
	gameMode = Cast<ATowerDefenceGameGameModeBase>(GetWorld()->GetAuthGameMode());
}

void UPlayerHUD::UpdateWave_Implementation(int WaveNumber)
{
	
}

void UPlayerHUD::UpdateMoney_Implementation(int CurrentBalance)
{
}

void UPlayerHUD::OnWaveStart_Implementation()
{
	
}
