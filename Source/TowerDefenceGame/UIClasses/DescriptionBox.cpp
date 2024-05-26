// Fill out your copyright notice in the Description page of Project Settings.


#include "DescriptionBox.h"

#include "Components/Button.h"
#include "Components/MultiLineEditableTextBox.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingSubsystem.h"
#include "TowerDefenceGame/SupportClasses/HelperMethods.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"


void UDescriptionBox::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UDescriptionBox::UpdateDescription(const FString& BuildingID, EButtonState State)
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
				txtDescription->SetText(FText::FromString(description));
			}
		}
		break;
	case BUTTON_UNHOVERED:
		txtDescription->SetText(FText::FromString(""));
		break;
	}
}