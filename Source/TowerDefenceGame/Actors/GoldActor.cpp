// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldActor.h"

#include "Components/WidgetComponent.h"
#include "TowerDefenceGame/UIClasses/GoldLootBar.h"

AGoldActor::AGoldActor()
{
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComp->SetupAttachment(RootComponent);
	WidgetComp->SetDrawSize(FVector2d(200,40));
	WidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
}

void AGoldActor::BeginPlay()
{
	Super::BeginPlay();
	WidgetComp->SetVisibility(true);
	GoldLootBar = Cast<UGoldLootBar>(WidgetComp->GetWidget());

	mCurrentGold = mTotalGold;

	mGameMode = Cast<ATowerDefenceGameGameModeBase>(GetWorld()->GetAuthGameMode());
}

void AGoldActor::LootGold_Implementation()
{
	mCurrentGold--;

	if(GoldLootBar != nullptr) GoldLootBar->LootGold(mCurrentGold, mTotalGold);
	
	if(mGameMode && mCurrentGold <= 0) mGameMode->OnGameOverSignature.Broadcast();
}
