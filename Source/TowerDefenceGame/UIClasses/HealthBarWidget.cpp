// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

void UHealthBarWidget::Updater_Implementation(float Val)
{
	mNewHealthVal = Val;
	mNewHealthVal_AsPercent = Val/100;
}

void UHealthBarWidget::ProgressBarUpdater_Implementation()
{
}

void UHealthBarWidget::TextUpdater_Implementation()
{
}
