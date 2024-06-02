// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopMenu.h"

#include "PlayerHUD.h"

void UShopMenu::NativeConstruct()
{
	Super::NativeConstruct();

	SetupButtons();
}

void UShopMenu::Init_Implementation(UPlayerHUD* Hud)
{
	mHUD = Hud;
}

void UShopMenu::SetupButtons_Implementation()
{

}

void UShopMenu::OnButtonStateUpdate_Implementation(const FString& BuildingID, EButtonState State)
{
	mHUD->OnButtonStateUpdate(BuildingID, State);
}

