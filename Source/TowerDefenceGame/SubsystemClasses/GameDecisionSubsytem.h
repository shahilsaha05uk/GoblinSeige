// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameDecisionSubsytem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameDecisionMadeSignature);
UCLASS()
class TOWERDEFENCEGAME_API UGameDecisionSubsytem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameDecisionMadeSignature OnGameDecisionMade;

	UFUNCTION(BlueprintCallable)
	void Trigger_OnGameDecisionMade()
	{
		OnGameDecisionMade.Broadcast();
	}
};
