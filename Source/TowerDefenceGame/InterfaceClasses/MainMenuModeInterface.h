// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "UObject/Interface.h"
#include "MainMenuModeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMainMenuModeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOWERDEFENCEGAME_API IMainMenuModeInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateSoundMixVolume(ESoundValue SoundValue, float Volume);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TMap<TEnumAsByte<ESoundValue>, FSoundStruct> GetSoundMap();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TMap<TEnumAsByte<ESoundValue>, float> ReadSoundSettingsFromFile();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void WriteSoundSettingsToFile();
	
};
