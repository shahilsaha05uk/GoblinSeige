// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/EnumClass.h"
#include "TowerDefenceGame/StructClass.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "Settings.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API USettings : public UBaseWidget
{
	GENERATED_BODY()

private:
	
	
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USlider* sdr_MenuVolume;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USlider* sdr_GameVolume;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* txt_MenuVolume;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* txt_GameVolume;
	
	
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ManageSoundSlider(ESoundValue SoundValue, float Volume);
	

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateSoundMixVolume(ESoundValue SoundValue, float Volume);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SaveSettings();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnMenuVolumeChanged(float Value);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnGameVolumeChanged(float Value);
	
};
