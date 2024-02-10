// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingUI.h"

#include "Components/Button.h"
#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"


void UBuildingUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(btnUpgrade) btnUpgrade->OnClicked.AddDynamic(this, &UBuildingUI::OnUpgrade);
	if(btnMove) btnMove->OnClicked.AddDynamic(this, &UBuildingUI::OnMove);
	if(btnDestroy) btnDestroy->OnClicked.AddDynamic(this, &UBuildingUI::OnDestroy);
}

void UBuildingUI::InitialiseWidget_Implementation(ABaseBuilding* ParentBuilding)
{
	mParentBuilding = ParentBuilding;

	if(mParentBuilding)
	{
		mParentBuilding->OnBuildingFullyUpgradedSignature.AddDynamic(this, &UBuildingUI::OnFullyUpgraded);
	}
}

void UBuildingUI::OnFullyUpgraded_Implementation()
{
	btnUpgrade->SetIsEnabled(false);
}

void UBuildingUI::OnUpgrade_Implementation()
{
	OnUpgradeSignature.Broadcast();
}

void UBuildingUI::OnMove_Implementation()
{
}

void UBuildingUI::OnDestroy_Implementation()
{
}

