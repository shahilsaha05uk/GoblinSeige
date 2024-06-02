#include "PlayerHUD.h"

#include "DescriptionBox.h"
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
	mResourceSubsystem = GetWorld()->GetFirstLocalPlayerFromController()->GetSubsystem<UResourceSubsystem>();

	if (const auto PlacementSubs = GetGameInstance()->GetSubsystem<UBuildingPlacementSubsystem>())
	{
		PlacementSubs->OnPlacementStateUpdate.AddDynamic(this, &ThisClass::OnPlacementStateUpdated);
	}

	if(const auto BuildingSubs = GetGameInstance()->GetSubsystem<UBuildingSubsystem>())
	{
		BuildingSubs->OnBuildingInteractionBegin.AddDynamic(this, &ThisClass::OnBuildingInterationBegin);
		BuildingSubs->OnBuildingInteractionEnd.AddDynamic(this, &ThisClass::OnBuildingInterationEnd);
	}
	

	mShop->Init(this);
	mShop->OnShopButtonHovered.AddDynamic(this, &ThisClass::OnShopButtonHovered);
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
		ToggleDescriptionBox(false);
		break;
	case SelectedPlacement:
		ToggleShop(true);
		break;
	case DeselectedPlacement:
		ToggleShop(false);
		break;
	case DecisionPlacement:
		ToggleShop(false);
		break;
	case OccupiedPlacement:
		ToggleShop(false);
		ToggleDescriptionBox(false);
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

#pragma region Shop methods

void UPlayerHUD::OnShopButtonHovered(FBuildingBuyDetails BuildingDetails)
{
	//mDescriptionBox->UpdateDescription(BuildingDetails);
}

void UPlayerHUD::OnBuildingInterationBegin_Implementation(ABaseBuilding* BuildingRef)
{
	mDescriptionBox->UpdateDescriptionWithUpgrade(BuildingRef);
}

void UPlayerHUD::OnBuildingInterationEnd_Implementation(ABaseBuilding* BuildingRef)
{
}

void UPlayerHUD::ToggleDescriptionBox_Implementation(bool Activate)
{
	
}

#pragma endregion
