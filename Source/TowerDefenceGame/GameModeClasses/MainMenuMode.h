// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenceGame/InterfaceClasses/MainMenuModeInterface.h"
#include "MainMenuMode.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API AMainMenuMode : public AGameModeBase, public IMainMenuModeInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound")
	TMap<TEnumAsByte<ESoundValue>, FSoundStruct> mSoundMap;


	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init();

	virtual TMap<TEnumAsByte<ESoundValue>, FSoundStruct> GetSoundMap_Implementation() override { return mSoundMap; }

	virtual TMap<TEnumAsByte<ESoundValue>, float> ReadSoundSettingsFromFile_Implementation() override;

	virtual void UpdateSoundMixVolume_Implementation(ESoundValue SoundValue, float Volume) override;

	virtual void WriteSoundSettingsToFile_Implementation() override;

};
