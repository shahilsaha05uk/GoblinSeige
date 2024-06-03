// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "TowerDefenceGame/SubsystemClasses/ClockSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/WaveSubsystem.h"

void UTimerComponent::BeginPlay()
{
	Super::BeginPlay();

	if(const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
	{
		mClockSubsystem = LocalPlayer->GetSubsystem<UClockSubsystem>();
		mClockSubsystem->ForceStopTimer.AddDynamic(this, &UTimerComponent::FinishTimer);
	}

	if(const UWorld* world = GetWorld())
	{
		mWaveSubsystem = world->GetGameInstance()->GetSubsystem<UWaveSubsystem>();
		if(mWaveSubsystem)
		{
			mWaveSubsystem->OnWaveUpdated.AddDynamic(this, &ThisClass::OnWaveComplete);
		}
	}
	FetchAndUpdateCountdownDetails();
	StartTimer();
}

void UTimerComponent::UpdateTimer()
{
	const FString timeToStr = UKismetStringLibrary::TimeSecondsToString(cTime);
	mClockSubsystem->CurrentTime.Broadcast(timeToStr);
}

void UTimerComponent::StartTimer()
{
	cTime = mCountDownTimerDetails.CountDownTimer;
	mClockSubsystem->StartTimer.Broadcast();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::Countdown, mRate, true);
}

void UTimerComponent::Countdown_Implementation()
{
	if(cTime > 0.0f)
	{
		const float Val = cTime - mRate;
		cTime = UKismetMathLibrary::FClamp(Val, 0.0f, 100000.0f);
		UpdateTimer();
	}
	else
	{
		FinishTimer();
		mClockSubsystem->FinishTimer.Broadcast();
	}
	
}

void UTimerComponent::FinishTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TimerHandle.Invalidate();
	cTime = 0.0f;
	UpdateTimer();
}

// Updating the Countdown Timer Details
bool UTimerComponent::FetchAndUpdateCountdownDetails()
{
	if(mDACountDownTimer)
	{
		if(mDACountDownTimer->GetCountDownDetails(mWaveSubsystem->GetCurrentWave(), mCountDownTimerDetails))
		{
			return true;
		}
	}
	return false;
}

void UTimerComponent::OnWaveComplete(int Wave)
{
	if(Wave > mCountDownTimerDetails.MaxLevel)
	{
		if(FetchAndUpdateCountdownDetails())
		{
			StartTimer();
		}
	}
	else
	{
		StartTimer();
	}
}