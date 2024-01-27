// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGame/TowerDefenceGameGameModeBase.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
	
	gameMode = Cast<ATowerDefenceGameGameModeBase>(GetWorld()->GetAuthGameMode());

	if(gameMode)
	{
		gameMode->OnWaveStartSignature.AddDynamic(this, &UPlayerHUD::OnWaveStart);
	}
}

void UPlayerHUD::OnWaveStart_Implementation()
{
	
}
