// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "WaveWidget.generated.h"


UCLASS()
class TOWERDEFENCEGAME_API UWaveWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UTextBlock* txtWave;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void OnWaveUpdate(int Wave);
};
