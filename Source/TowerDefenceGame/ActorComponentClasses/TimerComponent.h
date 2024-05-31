// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerValueUpdateSignature, FString, Time);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class TOWERDEFENCEGAME_API UTimerComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float mTotalduration;
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float mRate;
	UPROPERTY(BlueprintReadWrite)
	float cTime;
	UPROPERTY(BlueprintReadOnly)
	class UClockSubsystem* mClockSubsystem;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTimerValueUpdateSignature OnTimerUpdate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTimerHandle TimerHandle;

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Countdown();
	
	UFUNCTION(BlueprintCallable)
	void StartTimer();
	UFUNCTION(BlueprintCallable)
	void FinishTimer();
};
