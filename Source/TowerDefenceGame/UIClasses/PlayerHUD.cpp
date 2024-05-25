// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "Components/Button.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/WidgetSwitcher.h"
#include "TowerDefenceGame/BaseClasses/GameHUD.h"
#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/WaveSubsystem.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	btnUpgrade->OnClicked.AddDynamic(this, &UPlayerHUD::OnUpgradeButtonClick);
	btnMove->OnClicked.AddDynamic(this, &UPlayerHUD::OnMoveButtonClick);
	btnWaveStart->OnClicked.AddDynamic(this, &UPlayerHUD::OnWaveStart);

	mWaveSubsystem = GetGameInstance()->GetSubsystem<UWaveSubsystem>();
	mResourceSubsystem = GetGameInstance()->GetSubsystem<UResourceSubsystem>();

	if(mResourceSubsystem)
	{
		UpdateMoney();
		UpdateWave();
	}
	if(mWaveSubsystem)
	{
		mWaveSubsystem->OnWaveComplete.AddDynamic(this, &ThisClass::OnWaveComplete);
	}

	BuyMenuSetup();
}

void UPlayerHUD::UpdateMoney()
{
	txtMoney->SetText(FText::AsNumber(mResourceSubsystem->GetCurrentResources()));
}

void UPlayerHUD::UpdateWave()
{
	txtWave->SetText(FText::AsNumber(mWaveSubsystem->GetCurrentWave()));
}

void UPlayerHUD::BuyMenuSetup_Implementation()
{
	
}

void UPlayerHUD::PopulateBuildingButtons_Implementation(class UBuyButton* ButtonRef)
{
	
}

void UPlayerHUD::OpenBuildingSettingsUI_Implementation(ABaseBuilding* Building)
{
	BuildingRef = Building;
	FString txtToDisplay;
	FLinearColor colorToAdd;

	FTextBlockStyle style = txtDescriptionUpgradeMenu->WidgetStyle.TextStyle;
	style.SetColorAndOpacity(colorToAdd);

	txtDescriptionUpgradeMenu->SetTextStyle(style);
	
	txtDescriptionUpgradeMenu->SetText(FText::FromString(txtToDisplay));
	
	wsMenuSwitcher->SetActiveWidget(vbBuildingSettings);
}

void UPlayerHUD::WidgetToggler_Implementation(ABaseBuilding* Building)
{
	if(Building) OpenBuildingSettingsUI(Building);
	else wsMenuSwitcher->SetActiveWidget(vbShop);
}

void UPlayerHUD::OnWaveStart_Implementation()
{
	if(mWaveSubsystem)
	{
		mWaveSubsystem->StartWave();
		btnWaveStart->SetIsEnabled(false);
	}
}

#pragma region On Events Triggered

void UPlayerHUD::OnWaveComplete_Implementation(int WaveNumber)
{
}

void UPlayerHUD::OnMoveButtonClick_Implementation()
{
	OnMoveButtonClickedSignature.Broadcast();
}

void UPlayerHUD::OnUpgradeButtonClick_Implementation()
{
	if(BuildingRef)
	{
		OnUpgradeButtonClickedSignature.Broadcast(BuildingRef, BuildingRef->GetUpgradeCost());
	}
}

#pragma endregion