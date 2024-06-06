// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "TowerDefenceGame/DataAssetClasses/DA_CountdownTimer.h"
#include "TimerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartTimerSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishedTimerSignature);    // when the timer automatically finishes

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class TOWERDEFENCEGAME_API UTimerComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	
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

	UPROPERTY(BlueprintReadOnly)
	class UGameSubsystem* mGameSubsystem;

	FStartTimerSignature OnStartTimer;

	FFinishedTimerSignature OnFinishTimer;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void UpdateTimer();
	
	UFUNCTION(BlueprintCallable)
	void StopAndResetTimer();

	UFUNCTION(BlueprintCallable)
	void StartTimer(const float Duration);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Countdown();

	UFUNCTION(BlueprintCallable)
	void FinishTimer();
};
