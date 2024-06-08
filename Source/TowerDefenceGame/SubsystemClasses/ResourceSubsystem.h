// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourceSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResourceUpdatedSignature, int, CurrentBalance);

UCLASS()
class TOWERDEFENCEGAME_API UResourceSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

private:

	int mCurrentResources = 0;
	
	int TotalSpentResources = 0;
	
public:

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnResourceUpdatedSignature OnResourceUpdated;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCurrentResources() {return mCurrentResources;}
	
	UFUNCTION(BlueprintCallable)
	void Add(int value)
	{
		mCurrentResources += value;
		OnResourceUpdated.Broadcast(mCurrentResources);
	}

	UFUNCTION(BlueprintCallable)
	void Set(int value)
	{
		mCurrentResources = value;
		OnResourceUpdated.Broadcast(mCurrentResources);
	}

	UFUNCTION(BlueprintCallable)
	void Deduct(int value)
	{
		TotalSpentResources += value;
		
		mCurrentResources -= value;
		OnResourceUpdated.Broadcast(mCurrentResources);
	}

	UFUNCTION(BlueprintCallable)
	void AddPercentageOftheSpentMoney(float Percent)
	{
		const float val = GetPercentageOfTheTotalSpentMoney(Percent);
		Add(val);
	}
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetPercentageOfTheTotalSpentMoney(float Percent)
	{
		return FMath::RoundToInt(TotalSpentResources * Percent / 100.0f);
	}
};
