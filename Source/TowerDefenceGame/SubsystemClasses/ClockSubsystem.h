// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ClockSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartTimerSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishedTimerSignature);    // when the timer automatically finishes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCurrentTimeSignature, const FString&, CurrentTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FForceStopTimerSignature);    // when the timer automatically finishes

UCLASS()
class TOWERDEFENCEGAME_API UClockSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FCurrentTimeSignature CurrentTime;

	FStartTimerSignature StartTimer;
	FFinishedTimerSignature FinishTimer;
	FForceStopTimerSignature ForceStopTimer;
};
