// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "PlayerHUD.generated.h"



UCLASS()
class TOWERDEFENCEGAME_API UPlayerHUD : public UBaseWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	class ATowerDefenceGameGameModeBase* gameMode;
	
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnWaveStart();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateMoney(int CurrentBalance);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateWave(int WaveNumber);
};
