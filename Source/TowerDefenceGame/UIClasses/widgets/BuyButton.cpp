// Fill out your copyright notice in the Description page of Project Settings.


#include "BuyButton.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/MultiLineEditableTextBox.h"
#include "TowerDefenceGame/SupportClasses/HelperMethods.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"


void UBuyButton::Init()
{
	// Button binds to the different Events
	BuyButton->OnClicked.AddDynamic(this, &UBuyButton::OnBuyButtonClicked);
	BuyButton->OnHovered.AddDynamic(this, &ThisClass::OnButtonHovered);
	BuyButton->OnUnhovered.AddDynamic(this, &ThisClass::OnButtonUnhovered);

	// Binds the button to the Resource Subsystem
	mResourceSubsystem = GetGameInstance()->GetSubsystem<UResourceSubsystem>();

	if(mResourceSubsystem)
		mResourceSubsystem->OnResourceUpdated.AddDynamic(this, &ThisClass::OnResourceUpdated);

	/*
	if(const auto BuildingSubsystem = GetGameInstance()->GetSubsystem<UBuildingSubsystem>())
		BuildingSubsystem->OnBuildingRequestedForBuy.AddDynamic(this, &ThisClass::OnBuildRequest);
		*/

	// if the Building asset is valid, this will update the button styles
	defaultStyle = BuyButton->GetStyle();
	defaultStyle.Normal.DrawAs = ESlateBrushDrawType::Image;
	defaultStyle.Normal.SetResourceObject(mBuildingDetails.BuildingImage);
	defaultStyle.Hovered.DrawAs = ESlateBrushDrawType::Image;
	defaultStyle.Hovered.SetResourceObject(mBuildingDetails.BuildingImage);
	defaultStyle.Disabled.DrawAs = ESlateBrushDrawType::Image;
	defaultStyle.Disabled.SetResourceObject(mBuildingDetails.BuildingImage);

	// Set the Button Style
	BuyButton->SetStyle(defaultStyle);
	
	UpdateButton();		// Updates the button state
}

void UBuyButton::UpdateButtonState_Implementation(EButtonState State)
{
	if(ButtonColorMap.Contains(State))
	{
		ButtonBorder->SetBrushColor(ButtonColorMap[State]);
	}

	OnButtonStateUpdate.Broadcast(mBuildingDetails.ID, State);
}

void UBuyButton::OnButtonHovered_Implementation()
{
	UpdateButtonState(BUTTON_HOVERED);
}

void UBuyButton::OnButtonUnhovered_Implementation()
{
	UpdateButtonState(BUTTON_UNHOVERED);
}

void UBuyButton::OnBuyButtonClicked_Implementation()
{
	GetGameInstance()->GetSubsystem<UBuildingSubsystem>()->OnBuildingRequestedForBuy.Broadcast(mBuildingDetails.ID);
}

void UBuyButton::UpdateButton_Implementation()
{
	if(mResourceSubsystem)
	{
		const bool ShouldEnable = (mResourceSubsystem->GetCurrentResources() > mBuildingDetails.BuildingCost);
		BuyButton->SetIsEnabled(ShouldEnable);
		UpdateButtonState((ShouldEnable) ? BUTTON_ENABLED : BUTTON_DISABLED);
	}
}

void UBuyButton::OnResourceUpdated_Implementation(int CurrentBalance)
{
	UpdateButton();
}

void UBuyButton::OnBuildRequest_Implementation()
{
		
}