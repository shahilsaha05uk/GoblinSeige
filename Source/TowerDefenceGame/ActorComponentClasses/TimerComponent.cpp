// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "TowerDefenceGame/SubsystemClasses/ClockSubsystem.h"

void UTimerComponent::BeginPlay()
{
	Super::BeginPlay();

	if(const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
	{
		mClockSubsystem = LocalPlayer->GetSubsystem<UClockSubsystem>();
	}
}

void UTimerComponent::StartTimer()
{
	mClockSubsystem->StartTimer.Broadcast();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::Countdown, mRate, true);
}

void UTimerComponent::Countdown_Implementation()
{
	if(cTime > 0.0f)
	{
		float Val = cTime - mRate;
		cTime = UKismetMathLibrary::FClamp(Val, 0.0f, 100000.0f);
	}
	else
	{
		FinishTimer();
	}
	
	FString timeToStr = UKismetStringLibrary::TimeSecondsToString(cTime);
	mClockSubsystem->CurrentTime.Broadcast(timeToStr);
}

void UTimerComponent::FinishTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TimerHandle.Invalidate();
	OnTimerUpdate.Broadcast(UKismetStringLibrary::TimeSecondsToString(0.0f));
	mClockSubsystem->FinishTimer.Broadcast();
}


