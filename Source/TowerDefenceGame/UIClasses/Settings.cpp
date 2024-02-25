// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings.h"

#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"
#include "TowerDefenceGame/InterfaceClasses/MainMenuModeInterface.h"

void USettings::NativeConstruct()
{
	Super::NativeConstruct();

	Init();
}

void USettings::UpdateSoundMixVolume_Implementation(ESoundValue SoundValue, float Volume)
{
	const UWorld* World = GetWorld();
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);
	if(UKismetSystemLibrary::DoesImplementInterface(UGameplayStatics::GetGameMode(World), UMainMenuModeInterface::StaticClass()))
	{
		IMainMenuModeInterface::Execute_UpdateSoundMixVolume(GameMode, SoundValue, Volume);
	}
	
}

void USettings::SaveSettings_Implementation()
{
	const UWorld* World = GetWorld();
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);
	if(UKismetSystemLibrary::DoesImplementInterface(UGameplayStatics::GetGameMode(World), UMainMenuModeInterface::StaticClass()))
	{
		IMainMenuModeInterface::Execute_WriteSoundSettingsToFile(GameMode);
	}
}

void USettings::Init_Implementation()
{
	// Slider Binder
	sdr_GameVolume->OnValueChanged.AddDynamic(this, &USettings::OnGameVolumeChanged);
	sdr_MenuVolume->OnValueChanged.AddDynamic(this, &USettings::OnMenuVolumeChanged);
	
	//Check if the file exists
	TMap<TEnumAsByte<ESoundValue>, FSoundStruct> mSoundMap;

	const UWorld* World = GetWorld();
	if(UKismetSystemLibrary::DoesImplementInterface(UGameplayStatics::GetGameMode(World), UMainMenuModeInterface::StaticClass()))
	{
		mSoundMap = IMainMenuModeInterface::Execute_GetSoundMap(UGameplayStatics::GetGameMode(World));
	}

	if(!mSoundMap.IsEmpty())
	{
		for (auto e : mSoundMap)
		{
			float value = e.Value.SoundClassRef->Properties.Volume;

			ManageSoundSlider(e.Key, value);
		}
	}
}

void USettings::OnMenuVolumeChanged_Implementation(float Value)
{
	ManageSoundSlider(MENU_SOUND_VALUE, Value);
	UpdateSoundMixVolume(MENU_SOUND_VALUE, Value);
}

void USettings::OnGameVolumeChanged_Implementation(float Value)
{
	ManageSoundSlider(GAME_SOUND_VALUE, Value);
	UpdateSoundMixVolume(GAME_SOUND_VALUE, Value);
}

void USettings::ManageSoundSlider_Implementation(ESoundValue SoundValue, float Volume)
{
	switch (SoundValue)
	{
	case NO_SOUND_VALUE:
		break;
	case GAME_SOUND_VALUE:
		sdr_GameVolume->SetValue(Volume);
		txt_GameVolume->SetText(FText::FromString(FString::Printf(TEXT("%f"), Volume)));
		break;
	case MENU_SOUND_VALUE:
		sdr_MenuVolume->SetValue(Volume);
		txt_MenuVolume->SetText(FText::FromString(FString::Printf(TEXT("%f"), Volume)));
		break;
	default:
		break;
	}
}
