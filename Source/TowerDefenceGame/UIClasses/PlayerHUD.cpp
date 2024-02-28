// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "Components/Button.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/WidgetSwitcher.h"
#include "TowerDefenceGame/BaseClasses/GameHUD.h"
#include "TowerDefenceGame/GameModeClasses/TowerDefenceGameGameModeBase.h"
#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"
#include "TowerDefenceGame/ManagerClasses/WaveManager.h"

using namespace std;

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	btnUpgrade->OnClicked.AddDynamic(this, &UPlayerHUD::OnUpgradeButtonClick);
	btnMove->OnClicked.AddDynamic(this, &UPlayerHUD::OnMoveButtonClick);
	btnWaveStart->OnClicked.AddDynamic(this, &UPlayerHUD::OnWaveStart);
	
	gameMode = Cast<ATowerDefenceGameGameModeBase>(GetWorld()->GetAuthGameMode());

	if(gameMode)
	{
		gameMode->OnWaveCompleteSignature.AddDynamic(this, &ThisClass::OnWaveComplete);
	}

	BuyMenuSetup();
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

	GetStringForBuilding(BuildingRef, colorToAdd, txtToDisplay);

	Updater(BUILDING_NAME_VALUE, BuildingRef->BuildingDetails.BuildingName);

	FTextBlockStyle style = txtDescriptionUpgradeMenu->WidgetStyle.TextStyle;
	style.SetColorAndOpacity(colorToAdd);

	txtDescriptionUpgradeMenu->SetTextStyle(style);
	
	txtDescriptionUpgradeMenu->SetText(FText::FromString(txtToDisplay));
	
	wsMenuSwitcher->SetActiveWidget(vbBuildingSettings);
}

void UPlayerHUD::GetStringForBuilding(ABaseBuilding* Building, FLinearColor& colorToAdd, FString& txtToAdd)
{
	bool isUpgradeAvailable = Building->isUpgradeAvailable();
	bool hasEnoughMoney = (mCurrentBalance >= Building->GetUpgradeCost());

	FLinearColor red = FLinearColor(1, 0, 0, 1);
	FLinearColor green = FLinearColor(0, 1, 0, 1);

	if(!isUpgradeAvailable)
	{
		txtToAdd = "This Building is fully upgraded";
		btnUpgrade->SetIsEnabled(false);
		colorToAdd = red;
	}
	else
	{
		if(hasEnoughMoney)
		{
			txtToAdd = Building->GetBuildingUpgradeDescription() + "You can upgrade this building";
			btnUpgrade->SetIsEnabled(true);
			colorToAdd = green;
		}
		else
		{
			const int MoneyToAcquire = BuildingRef->GetUpgradeCost() - mCurrentBalance;
			txtToAdd = Building->GetBuildingUpgradeDescription() + FString::Printf(TEXT("\nYou require £ %d to upgrade this building"), MoneyToAcquire);
			btnUpgrade->SetIsEnabled(false);
			colorToAdd = red;
		}
	}
}

void UPlayerHUD::WidgetToggler_Implementation(ABaseBuilding* Building)
{
	if(Building) OpenBuildingSettingsUI(Building);
	else wsMenuSwitcher->SetActiveWidget(vbShop);
}

void UPlayerHUD::OnWaveStart_Implementation()
{
	if(gameMode)
	{
		IGameModeInterface::Execute_GetWaveManager(gameMode)->StartWave();

		btnWaveStart->SetIsEnabled(false);
	}
}

#pragma region Updaters

void UPlayerHUD::UpdateIntValues(EHudValue ValueType, int Value)
{
	switch (ValueType)
	{
	case MONEY_VALUE:
		{
			mCurrentBalance = Value;

			const FString BalanceAsString = FString::Printf(TEXT("£ %d"), mCurrentBalance);
		
			txtMoney->SetText(FText::FromString(BalanceAsString));
			txtMoneyUpgradeMenu->SetText(FText::FromString(BalanceAsString));
			break;
		}
	case WAVE_VALUE:
		txtWave->SetText(FText::AsNumber(Value));
		break;
	default: ;
	}
}

void UPlayerHUD::UpdateStringValues(EHudValue ValueType, FString Value)
{
	switch (ValueType) {
	case BUILDING_NAME_VALUE:
		
		txtBuildingNameUpgradeMenu->SetText(FText::FromString(Value));
		break;
	}
}

void UPlayerHUD::PostWidgetUpdate_Implementation(EHudValue ValueType)
{
	switch (ValueType) {
	case MONEY_VALUE:
		OnCurrentBalanceUpdated.Broadcast(mCurrentBalance);
		break;
	case WAVE_VALUE:
		break;
	case BUILDING_NAME_VALUE:
		break;
	}
}

#pragma endregion

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