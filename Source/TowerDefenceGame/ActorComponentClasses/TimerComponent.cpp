// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "TowerDefenceGame/SubsystemClasses/ClockSubsystem.h"


#pragma region Starters

void UTimerComponent::BeginPlay()
{
	Super::BeginPlay();

	if(const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
	{
		mClockSubsystem = LocalPlayer->GetSubsystem<UClockSubsystem>();
	}
}

void UTimerComponent::StartTimer(const float Duration)
{
	cTime = Duration;
	OnStartTimer.Broadcast();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::Countdown, mRate, true);
}

#pragma endregion

#pragma region Updaters

void UTimerComponent::UpdateTimer()
{
	const FString timeToStr = UKismetStringLibrary::TimeSecondsToString(cTime);
	mClockSubsystem->CurrentTime.Broadcast(timeToStr);
}

void UTimerComponent::Countdown_Implementation()
{
	if(cTime > 0.0f)
	{
		const float Val = cTime - mRate;
		cTime = UKismetMathLibrary::FClamp(Val, 0.0f, 100000.0f);
	}
	else
	{
		FinishTimer();
		OnFinishTimer.Broadcast();
	}

	UpdateTimer();
}

#pragma endregion

#pragma region Finish Timers

void UTimerComponent::FinishTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TimerHandle.Invalidate();

	cTime = 0.0f;

	UpdateTimer();
}

void UTimerComponent::StopAndResetTimer()
{
	FinishTimer();
}
#pragma endregion
