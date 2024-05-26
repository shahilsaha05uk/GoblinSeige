// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopMenu.h"

#include "Components/MultiLineEditableTextBox.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "TowerDefenceGame/SupportClasses/HelperMethods.h"

void UShopMenu::NativeConstruct()
{
	Super::NativeConstruct();

	SetupButtons();
}

void UShopMenu::SetupButtons_Implementation()
{

}

void UShopMenu::OnButtonStateUpdate_Implementation(const FString& BuildingID, EButtonState State)
{
	switch (State) {
	case BUTTON_ENABLED:

		break;
	case BUTTON_DISABLED:

		break;
	case BUTTON_HOVERED:
		{
			FBuildingBuyDetails Details;
			if(mBuildingAsset->FindBuildingDetails(BuildingID, Details))
			{
				const auto description = UHelperMethods::GetDescription(Details.BuildingStats);
				UpdateDescription(description);
			}
		}
		break;
	case BUTTON_UNHOVERED:
		UpdateDescription("");
		break;
	}
}

void UShopMenu::UpdateDescription(const FString& Description)
{
	txtDescription->SetText(FText::FromString(Description));
}
