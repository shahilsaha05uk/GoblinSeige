// Fill out your copyright notice in the Description page of Project Settings.


#include "BuyButton.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/MultiLineEditableTextBox.h"
#include "TowerDefenceGame/SupportClasses/HelperMethods.h"
#include "TowerDefenceGame/ControllerClasses/InputController.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"
#include "TowerDefenceGame/UIClasses/PlayerHUD.h"


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

	if(auto resourceSubs = GetGameInstance()->GetSubsystem<UResourceSubsystem>())
	{
		const bool ButtonEnableCheck = resourceSubs->GetCurrentResources() > mBuildingAsset->BuildingCost;

		const EButtonState ButtonState = (ButtonEnableCheck) ? BUTTON_ENABLED : BUTTON_DISABLED;

		BuyButton->SetIsEnabled(ButtonEnableCheck);
	
		UpdateButtonState(ButtonState);
	}
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
	UpdateButtonState(BUTTON_HOVERED);

	UpdateDescription(!BuyButton->GetIsEnabled());

}

void UBuyButton::OnButtonUnhovered_Implementation()
{
	UpdateButtonState(BUTTON_UNHOVERED);
	UpdateDescription(true);
}

void UBuyButton::OnCurrentBalanceUpdated_Implementation(int CurrentBalance)
{
	bool ShouldEnable = IsCurrentBalanceLessThanTheBuildingCost(CurrentBalance);
	const EButtonState ButtonState = (ShouldEnable) ? BUTTON_ENABLED : BUTTON_DISABLED;

	BuyButton->SetIsEnabled(ShouldEnable);
	
	UpdateButtonState(ButtonState);
}

void UBuyButton::OnBuyButtonClicked_Implementation()
{
	Controller->OnBuyMenuOptionClickSignature.Broadcast(mBuildingAsset);
}
