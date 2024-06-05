// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "Settings.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API USettings : public UBaseWidget
{
	GENERATED_BODY()


private:
	
	FString ResolutionValue;
	EGraphicsValue CurrentGraphics;

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UComboBoxString* cmb_Resolution;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btnResolutionApply;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btnSoundSettingsApply;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USlider* sdr_MenuVolume;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USlider* sdr_GameVolume;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* txt_MenuVolume;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* txt_GameVolume;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EGraphicsValue>> GraphicsValues;
	
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ManageSoundSlider(ESoundValue SoundValue, float Volume);
	

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateSoundMixVolume(ESoundValue SoundValue, float Volume);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnMenuVolumeChanged(float Value);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnGameVolumeChanged(float Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SaveSettingsToFile(ESettingsToSave SettingsToSave);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSoundSettingsApply();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ApplyResolution();
	
	UFUNCTION(BlueprintCallable)
	void OnResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
};
