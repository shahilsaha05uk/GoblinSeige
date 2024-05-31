// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameDecisionMadeSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHUDInitialisedSignature, AHUD*, HudRef);

UCLASS()
class TOWERDEFENCEGAME_API UGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:

	UPROPERTY()
	AHUD* mHud;

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameDecisionMadeSignature OnGameDecisionMade;
	UPROPERTY(BlueprintAssignable)
	FOnHUDInitialisedSignature OnHudInitialised;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AHUD* GetHudRef() {return mHud;}
	
	UFUNCTION(BlueprintCallable)
	void InitialiseHud(AHUD* HudRef)
	{
		mHud = HudRef;
		OnHudInitialised.Broadcast(mHud);
	}
};
