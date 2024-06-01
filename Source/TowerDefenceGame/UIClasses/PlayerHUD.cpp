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
}

void UPlayerHUD::OnButtonStateUpdate_Implementation(const FString& String, EButtonState State)
{
}

void UPlayerHUD::ToggleShop_Implementation(bool Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Open the shop"));
}
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
