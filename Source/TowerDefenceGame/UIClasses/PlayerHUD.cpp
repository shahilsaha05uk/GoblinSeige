#include "PlayerHUD.h"
#include "ShopMenu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingPlacementSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingSubsystem.h"
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

	if (const auto PlacementSubs = GetGameInstance()->GetSubsystem<UBuildingPlacementSubsystem>())
	{
		PlacementSubs->OnPlacementStateUpdate.AddDynamic(this, &ThisClass::OnPlacementStateUpdated);
	}

	if (const auto BuildingSubsystem = GetGameInstance()->GetSubsystem<UBuildingSubsystem>())
	{
		BuildingSubsystem->OnBuildingRequestedForBuy.AddDynamic(this, &ThisClass::OnRequestForBuildingBuy);
		BuildingSubsystem->OnBuildDecisionTaken.AddDynamic(this, &ThisClass::OnBuildingDecisionTaken);
	}

	/*
	if (const auto BuildingSubsystem = GetGameInstance()->GetSubsystem<UBuildingSubsystem>())
	{
		//BuildingSubsystem->OnPlacementActorSelected.AddDynamic(this, &ThisClass::OnPlacementSelected);
		BuildingSubsystem->OnBuildingRequestedForBuy.AddDynamic(this, &ThisClass::OnRequestForBuildingBuy);
		BuildingSubsystem->OnBuildDecisionTaken.AddDynamic(this, &ThisClass::OnBuildingDecisionTaken);
	}
	*/

	/*if(mWaveSubsystem)
	{
		mWaveSubsystem->OnWaveComplete.AddDynamic(this, &ThisClass::OnWaveComplete);
	}*/
}

void UPlayerHUD::OnButtonStateUpdate_Implementation(const FString& String, EButtonState State)
{
}

void UPlayerHUD::ToggleShop_Implementation(bool Value)
{
	//TODO: the radial comes up here
	UE_LOG(LogTemp, Warning, TEXT("Open the shop"));
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


#pragma region Building Methods

void UPlayerHUD::OnPlacementStateUpdated(EPlacementState State, APlacementActor* PlacementActor)
{
	switch (State) {
	case EmptyPlacement:
		break;
	case SelectedPlacement:
		ToggleShop(true);
		break;
	case DeselectedPlacement:
		ToggleShop(false);
		break;
	case DecisionPlacement:
		break;
	case OccupiedPlacement:
		break;
	}
}

void UPlayerHUD::OnBuildingDecisionTaken_Implementation(EBuildStatus Status)
{
	ToggleShop(false);
}

void UPlayerHUD::OnRequestForBuildingBuy_Implementation(const FString& BuildingID)
{
	ToggleShop(false);
}

#pragma endregion
