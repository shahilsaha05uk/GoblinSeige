// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ClockSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCurrentTimeSignature, const FString&, CurrentTime);

UCLASS()
class TOWERDEFENCEGAME_API UClockSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FCurrentTimeSignature CurrentTime;

};
