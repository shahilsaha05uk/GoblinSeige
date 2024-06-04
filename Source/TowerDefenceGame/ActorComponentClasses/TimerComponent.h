// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "TowerDefenceGame/DataAssetClasses/DA_CountdownTimer.h"
#include "TimerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class TOWERDEFENCEGAME_API UTimerComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class UWaveSubsystem* mWaveSubsystem;
	
	UPROPERTY()
	FTimerHandle TimerHandle;

	UPROPERTY()
	float mTotalDuration;

	UPROPERTY(EditDefaultsOnly)
	float mRate;

	UPROPERTY()
	float cTime;

	UPROPERTY()
	class UClockSubsystem* mClockSubsystem;

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void UpdateTimer();
	
	UFUNCTION(BlueprintCallable)
	void ForceStopTimer();
	UFUNCTION(BlueprintCallable)
	void StartTimer(const float Duration);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Countdown();
	UFUNCTION(BlueprintCallable)
	void FinishTimer();
};
