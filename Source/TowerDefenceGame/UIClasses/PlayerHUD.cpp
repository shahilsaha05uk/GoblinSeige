// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGame/GameHUD.h"
#include "TowerDefenceGame/TowerDefenceGameGameModeBase.h"
#include "TowerDefenceGame/ManagerClasses/WaveManager.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	btnUpgrade->OnClicked.AddDynamic(this, &UPlayerHUD::OnUpgradeButtonClick);
	btnMove->OnClicked.AddDynamic(this, &UPlayerHUD::OnMoveButtonClick);

	
	gameMode = Cast<ATowerDefenceGameGameModeBase>(GetWorld()->GetAuthGameMode());
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
