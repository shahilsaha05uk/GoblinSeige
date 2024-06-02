// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_CountdownTimer.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FWaveCountDownTimerDetails
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CountDownTimer;
};


UCLASS(Blueprintable, BlueprintType)
class TOWERDEFENCEGAME_API UDA_CountdownTimer : public UDataAsset
{
	GENERATED_BODY()


private:
	UPROPERTY(EditDefaultsOnly)
	TMap<int, FWaveCountDownTimerDetails> CountDownMap;

public:

	UFUNCTION(BlueprintCallable)
	bool GetCountDownDetails(int Wave, FWaveCountDownTimerDetails& Details);
};
