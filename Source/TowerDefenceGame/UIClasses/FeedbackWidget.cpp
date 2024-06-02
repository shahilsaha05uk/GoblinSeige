// Fill out your copyright notice in the Description page of Project Settings.


#include "FeedbackWidget.h"

#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/WaveSubsystem.h"

void UFeedbackWidget::Init_Implementation(UPlayerHUD* HudRef)
{
	mPlayerHUD = HudRef;

	if(const auto WaveSubs = GetGameInstance()->GetSubsystem<UWaveSubsystem>())
	{
		WaveSubs->OnWaveStarted.AddDynamic(this, &ThisClass::OnWaveStarted);
		WaveSubs->OnWaveUpdated.AddDynamic(this, &ThisClass::OnWaveEnded);
	}
	if(const auto GameSubs = GetGameInstance()->GetSubsystem<UGameSubsystem>())
	{
		GameSubs->OnDoorBroken.AddDynamic(this, &ThisClass::OnDoorBroken);
	}
}

void UFeedbackWidget::UpdateFeedback_Implementation(const FString& StrToDisplay)
{
}

void UFeedbackWidget::OnWaveStarted(int Wave)
{
	UpdateFeedback(TEXT("Wave %d has Started"));
}

void UFeedbackWidget::OnWaveEnded(int Wave)
{
	UpdateFeedback(TEXT("The Wave has Ended"));
}

void UFeedbackWidget::OnDoorBroken()
{
	UpdateFeedback(TEXT("The Goblins broke in!!!"));
}
