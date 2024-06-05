// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UHealthBarWidget : public UBaseWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* pbr_HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* txt_HealthVal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private")
	FTimerHandle Health_TimeHandler;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private")
	float mNewHealthVal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private")
	float mNewHealthVal_AsPercent;
	

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Updater(float Val);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ProgressBarUpdater();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TextUpdater();
};
