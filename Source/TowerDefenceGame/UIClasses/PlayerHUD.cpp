#include "PlayerHUD.h"
#include "ShopMenu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/WaveSubsystem.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	/*
	btnUpgrade->OnClicked.AddDynamic(this, &UPlayerHUD::OnUpgradeButtonClick);
	btnMove->OnClicked.AddDynamic(this, &UPlayerHUD::OnMoveButtonClick);
	*/
	btnWaveStart->OnClicked.AddDynamic(this, &UPlayerHUD::OnWaveStart);

	mWaveSubsystem = GetGameInstance()->GetSubsystem<UWaveSubsystem>();
	mResourceSubsystem = GetGameInstance()->GetSubsystem<UResourceSubsystem>();
	
	/*if(mWaveSubsystem)
	{
		mWaveSubsystem->OnWaveComplete.AddDynamic(this, &ThisClass::OnWaveComplete);
	}*/
}


/*

void UPlayerHUD::PopulateBuildingButtons_Implementation(class UBuyButton* ButtonRef)
{
	
}

void UPlayerHUD::OpenBuildingSettingsUI_Implementation(ABaseBuilding* Building)
{
	BuildingRef = Building;
	FString txtToDisplay;
	FLinearColor colorToAdd;
	wsMenuSwitcher->SetActiveWidget(vbBuildingSettings);
}
void UPlayerHUD::WidgetToggler_Implementation(ABaseBuilding* Building)
{
	if(Building) OpenBuildingSettingsUI(Building);
	else wsMenuSwitcher->SetActiveWidget(mShop);
}
*/


void UPlayerHUD::OnWaveStart_Implementation()
{
	if(mWaveSubsystem)
	{
		mWaveSubsystem->StartWave();
		//btnWaveStart->SetIsEnabled(false);
	}
}

#pragma region On Events Triggered


/*void UPlayerHUD::OnMoveButtonClick_Implementation()
{
	OnMoveButtonClickedSignature.Broadcast();
}

void UPlayerHUD::OnUpgradeButtonClick_Implementation()
{
	if(BuildingRef)
	{
		OnUpgradeButtonClickedSignature.Broadcast(BuildingRef, BuildingRef->GetUpgradeCost());
	}
}*/

#pragma endregion