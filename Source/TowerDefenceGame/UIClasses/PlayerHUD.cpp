// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "Components/Button.h"
#include "TowerDefenceGame/GameHUD.h"
#include "TowerDefenceGame/TowerDefenceGameGameModeBase.h"

using namespace std;

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	btnUpgrade->OnClicked.AddDynamic(this, &UPlayerHUD::OnUpgradeButtonClick);
	btnMove->OnClicked.AddDynamic(this, &UPlayerHUD::OnMoveButtonClick);

	
	gameMode = Cast<ATowerDefenceGameGameModeBase>(GetWorld()->GetAuthGameMode());

	if(gameMode)
	{
		gameMode->OnWaveCompleteSignature.AddDynamic(this, &ThisClass::OnWaveComplete);
	}
}

void UPlayerHUD::UpdateIntValues(EHudValue ValueType, int Value)
{
	switch (ValueType)
	{
	case MONEY_VALUE:
		UpdateMoney(Value);
		break;
	case WAVE_VALUE:
		UpdateWave(Value);
		break;
	default: ;
	}
}

void UPlayerHUD::UpdateFloatValues(EHudValue ValueType, float Value)
{
	
}


void UPlayerHUD::OnWaveComplete_Implementation(int WaveNumber)
{
}

void UPlayerHUD::OnBuildingSettingsMenuOpen_Implementation()
{
}

void UPlayerHUD::OnMoveButtonClick_Implementation()
{
	OnMoveButtonClickedSignature.Broadcast();
}

void UPlayerHUD::OnUpgradeButtonClick_Implementation()
{
	OnUpgradeButtonClickedSignature.Broadcast();
}

void UPlayerHUD::WidgetToggler_Implementation(ESideMenuSwitcher menu, bool isUpgradeAvailable)
{
	
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
