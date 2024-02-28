// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings.h"

#include "Components/Button.h"
#include "Components/ComboBox.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"
#include "TowerDefenceGame/InterfaceClasses/MainMenuModeInterface.h"
#include "TowerDefenceGame/SupportClasses/HelperMethods.h"

void USettings::NativeConstruct()
{
	Super::NativeConstruct();

	Init();
}

void USettings::SaveSettingsToFile_Implementation(ESettingsToSave SettingsToSave)
{
	const UWorld* World = GetWorld();
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);

	bool bDoesImplementInterface = UKismetSystemLibrary::DoesImplementInterface(GameMode, UMainMenuModeInterface::StaticClass());

	if(!bDoesImplementInterface) return;
	switch (SettingsToSave)
	{
	case SOUND_SETTINGS:
		IMainMenuModeInterface::Execute_WriteSoundSettingsToFile(GameMode);
		break;
	}
}


void USettings::Init_Implementation()
{
	// Slider Binder
	sdr_GameVolume->OnValueChanged.AddDynamic(this, &USettings::OnGameVolumeChanged);
	sdr_MenuVolume->OnValueChanged.AddDynamic(this, &USettings::OnMenuVolumeChanged);

	btnSoundSettingsApply->OnClicked.AddDynamic(this, &USettings::OnSoundSettingsApply);

	btnResolutionApply->OnClicked.AddDynamic(this, &USettings::ApplyResolution);
	cmb_Resolution->OnSelectionChanged.AddDynamic(this, &USettings::OnResolutionChanged);

	
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
	
	// Initialise the Resolution Array:
	for (auto r : GraphicsValues)
	{
		cmb_Resolution->AddOption(UEnum::GetValueAsString(r));
	}
}

void USettings::ApplyResolution_Implementation()
{
	EGraphicsValue graphicsEnumVal = UHelperMethods::GetGraphicsValueFromString(ResolutionValue);
	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();

	switch (graphicsEnumVal) {
	case FULLSCREEN:
		UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
		break;
	case WINDOWED:
		UserSettings->SetFullscreenMode(EWindowMode::Windowed);
		UserSettings->SetScreenResolution(FIntPoint(1920, 1080));
		break;
	}

	UserSettings->ApplyResolutionSettings(false);

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

// Widget Binded Methods
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

void USettings::OnSoundSettingsApply_Implementation()
{
	SaveSettingsToFile(SOUND_SETTINGS);
}

void USettings::OnResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	ResolutionValue = SelectedItem;
}