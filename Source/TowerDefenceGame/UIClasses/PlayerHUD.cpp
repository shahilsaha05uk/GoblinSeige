#include "PlayerHUD.h"

#include "DescriptionBox.h"
#include "FeedbackWidget.h"
#include "ShopMenu.h"
#include "Components/TextBlock.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingPlacementSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

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
	
	if(const auto GameSubs = GetGameInstance()->GetSubsystem<UGameSubsystem>())
	{
		GameSubs->OnFeedbackEnabled.AddDynamic(this, &ThisClass::OnFeedbackRecieved);
		GameSubs->OnGameComplete.AddDynamic(this, &ThisClass::OnGameComplete);
	}
	
	mShop->Init(this);
	mShop->OnShopButtonHovered.AddDynamic(this, &ThisClass::OnShopButtonHovered);
	mShop->OnShopButtonUnhover.AddDynamic(this, &ThisClass::OnShopUnhovered);
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
		break;
	}
}

void UPlayerHUD::OnBuildingDecisionTaken_Implementation(EBuildStatus Status)
{
	ToggleShop(false);
}

#pragma endregion

#pragma region Shop methods

void UPlayerHUD::OnShopButtonHovered(FBuildingBuyDetails BuildingDetails)
{
	mDescriptionBox->ModifyForBuy(BuildingDetails);
}

void UPlayerHUD::OnShopUnhovered()
{
	mDescriptionBox->ModifyWhenUnHovered();
}

void UPlayerHUD::OnBuildingInterationBegin_Implementation(ABaseBuilding* BuildingRef)
{
	mDescriptionBox->ModifyForUpgrade(BuildingRef);
}

void UPlayerHUD::OnBuildingInterationEnd_Implementation(ABaseBuilding* BuildingRef)
{
}

void UPlayerHUD::ToggleDescriptionBox_Implementation(bool Activate)
{
	
}

#pragma endregion

#pragma region Feedback

void UPlayerHUD::OnFeedbackRecieved_Implementation(EFeedbackType Type, const FString& MessageToDisplay)
{
	mFeedbackBox->UpdateFeedback(Type, MessageToDisplay);
}
#pragma endregion


void UPlayerHUD::OnGameComplete_Implementation(bool bWon)
{
	
}