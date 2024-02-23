// Fill out your copyright notice in the Description page of Project Settings.


#include "BuyButton.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/MultiLineEditableTextBox.h"
#include "TowerDefenceGame/HelperMethods.h"
#include "TowerDefenceGame/InputController.h"



void UBuyButton::Init_Implementation(UPlayerHUD* PlayerHUD, UMultiLineEditableTextBox* descriptionWidget, class UDA_BuildingAsset* BuildingAsset)
{
	PlayerHUDRef = PlayerHUD;
	txtDescription = descriptionWidget;
	mBuildingAsset = BuildingAsset;

	
	BuyButton->OnClicked.AddDynamic(this, &UBuyButton::OnBuyButtonClicked);
	BuyButton->OnHovered.AddDynamic(this, &ThisClass::OnButtonHovered);
	BuyButton->OnUnhovered.AddDynamic(this, &ThisClass::OnButtonUnhovered);

	if(PlayerHUDRef)
	{
		PlayerHUDRef->OnCurrentBalanceUpdated.AddDynamic(this, &ThisClass::OnCurrentBalanceUpdated);
	}
	if (mBuildingAsset)
	{
		defaultStyle = BuyButton->GetStyle();
		defaultStyle.Normal.DrawAs = ESlateBrushDrawType::Image;
		defaultStyle.Normal.SetResourceObject(mBuildingAsset->BuildingImage);
		defaultStyle.Hovered.DrawAs = ESlateBrushDrawType::Image;
		defaultStyle.Hovered.SetResourceObject(mBuildingAsset->BuildingImage);
		defaultStyle.Disabled.DrawAs = ESlateBrushDrawType::Image;
		defaultStyle.Disabled.SetResourceObject(mBuildingAsset->BuildingImage);
	}

	BuildingDescription = "Stats: \n" + UHelperMethods::GetDescription(mBuildingAsset->BuildingStats);

	BuyButton->SetStyle(defaultStyle);

	UpdateButtonState(BUTTON_ENABLED);
}

void UBuyButton::UpdateDescription_Implementation(bool bSetToDefault)
{
	const FString stringToAdd = (bSetToDefault)? "Description!!" : BuildingDescription;
	
	txtDescription->SetText(FText::FromString(stringToAdd));
}

void UBuyButton::UpdateButtonState_Implementation(EButtonState State)
{
	if(ButtonColorMap.Contains(State))
	{
		ButtonBorder->SetBrushColor(ButtonColorMap[State]);
	}
}

void UBuyButton::OnButtonHovered_Implementation()
{
}

void UBuyButton::OnButtonUnhovered_Implementation()
{
}

void UBuyButton::OnCurrentBalanceUpdated_Implementation(int CurrentBalance)
{
	BuyButton->SetIsEnabled(IsCurrentBalanceLessThanTheBuildingCost(CurrentBalance));
}

void UBuyButton::OnBuyButtonClicked_Implementation()
{
	Controller->OnBuyMenuOptionClickSignature.Broadcast(mBuildingAsset);
}
