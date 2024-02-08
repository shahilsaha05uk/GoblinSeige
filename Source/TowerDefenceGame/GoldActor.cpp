// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldActor.h"

#include "Components/WidgetComponent.h"
#include "UIClasses/GoldLootBar.h"

void AGoldActor::BeginPlay()
{
	Super::BeginPlay();
	WidgetComp->SetVisibility(true);
	//GoldLootBar = Cast<UGoldLootBar>(GoldLootBarComponent->GetWidget());
}

void AGoldActor::LootGold_Implementation()
{
	if(GoldLootBar != nullptr) GoldLootBar->LootGold(mCurrentGold, mTotalGold);
}
