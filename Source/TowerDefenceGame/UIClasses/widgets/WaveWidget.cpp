// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveWidget.h"

#include "Components/TextBlock.h"
#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"

void UWaveWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(const auto gameSubsystem = GetGameInstance()->GetSubsystem<UGameSubsystem>())
	{
		gameSubsystem->OnWaveUpdated.AddDynamic(this, &ThisClass::OnWaveUpdate);
		OnWaveUpdate(gameSubsystem->OnGetCurrentWave.Execute());
	}
}

void UWaveWidget::OnWaveUpdate(int Wave)
{
	txtWave->SetText(FText::AsNumber(Wave));
}
