// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveWidget.h"

#include "Components/TextBlock.h"
#include "TowerDefenceGame/SubsystemClasses/WaveSubsystem.h"

void UWaveWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(const auto WaveSubsystem = GetGameInstance()->GetSubsystem<UWaveSubsystem>())
	{
		WaveSubsystem->OnWaveUpdated.AddDynamic(this, &ThisClass::OnWaveUpdate);
		OnWaveUpdate(WaveSubsystem->GetCurrentWave());
	}
}

void UWaveWidget::OnWaveUpdate(int Wave)
{
	txtWave->SetText(FText::AsNumber(Wave));
}
