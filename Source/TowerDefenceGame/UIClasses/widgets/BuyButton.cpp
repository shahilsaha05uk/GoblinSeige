// Fill out your copyright notice in the Description page of Project Settings.


#include "BuyButton.h"

#include "Components/Button.h"

void UBuyButton::NativeConstruct()
{
	Super::NativeConstruct();

	BuyButton->OnClicked.AddDynamic(this, &UBuyButton::OnBuyButtonClicked);
}

void UBuyButton::OnBuyButtonClicked_Implementation()
{
	
}
