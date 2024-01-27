// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingUI.h"

#include "Components/Button.h"


void UBuildingUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(btnUpgrade) btnUpgrade->OnClicked.AddDynamic(this, &UBuildingUI::OnUpgrade);
	if(btnMove) btnMove->OnClicked.AddDynamic(this, &UBuildingUI::OnMove);
	if(btnDestroy) btnDestroy->OnClicked.AddDynamic(this, &UBuildingUI::OnDestroy);
}

void UBuildingUI::OnUpgrade_Implementation()
{
}

void UBuildingUI::OnMove_Implementation()
{
}

void UBuildingUI::OnDestroy_Implementation()
{
}

