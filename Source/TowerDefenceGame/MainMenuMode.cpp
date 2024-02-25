// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuMode.h"

#include "Sound/SoundClass.h"

void AMainMenuMode::UpdateSoundMixVolume_Implementation(ESoundValue SoundValue, float Volume)
{
	if(mSoundMap.Contains(SoundValue))
	{
		mSoundMap[SoundValue].SoundClassRef->Properties.Volume = Volume;
	}
}

void AMainMenuMode::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void AMainMenuMode::Init_Implementation()
{
	bool bSuccess = false;
	const TMap<TEnumAsByte<ESoundValue>, float> SoundSettings = ReadSoundSettings();

	if(!SoundSettings.IsEmpty())
	{
		for (auto e : mSoundMap)
		{
			e.Value.SoundClassRef->Properties.Volume = SoundSettings[e.Key];
		}
	}
}

TMap<TEnumAsByte<ESoundValue>, float> AMainMenuMode::ReadSoundSettingsFromFile_Implementation()
{
	return ReadSoundSettings();
}

void AMainMenuMode::WriteSoundSettingsToFile_Implementation()
{
	WriteSoundSettings();
}

TMap<TEnumAsByte<ESoundValue>, float> AMainMenuMode::ReadSoundSettings()
{
	TMap<TEnumAsByte<ESoundValue>, float> LoadedSettingsMap;
	FString LoadPath = FPaths::ProjectSavedDir() + TEXT("SoundSettings.json");
	FString LoadedString;

	if(FFileHelper::LoadFileToString(LoadedString, *LoadPath))
	{
		TSharedPtr<FJsonObject> RootObject;
		const TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(LoadedString);
		
		if(FJsonSerializer::Deserialize(reader, RootObject) && RootObject.IsValid())
		{
			for (auto e : RootObject->Values)
			{
				ESoundValue Key;
				FString KeyStr = e.Key;
				UEnum* enumVal = StaticEnum<ESoundValue>();
				int64 EnumVal = enumVal->GetValueByNameString(KeyStr);

				if(EnumVal != INDEX_NONE)
				{
					Key = static_cast<ESoundValue>(EnumVal);

					const TSharedPtr<FJsonObject>* SettingObject;
					if (e.Value->TryGetObject(SettingObject))
					{
						const float value = (*SettingObject)->GetNumberField(TEXT("Value"));
            
						float Volume = value;

						LoadedSettingsMap.Add(Key, Volume);
					}
				}
			}
			return LoadedSettingsMap;
		}
	}

	return TMap<TEnumAsByte<ESoundValue>, float>();
}

void AMainMenuMode::WriteSoundSettings()
{
	TSharedPtr<FJsonObject> RootObject = MakeShareable(new FJsonObject);

	for (auto e : mSoundMap)
	{
		FString keyString = UEnum::GetValueAsString(e.Key);

		TSharedPtr<FJsonObject> SettingsObject = MakeShareable(new FJsonObject);
		SettingsObject->SetNumberField(TEXT("Value"), e.Value.SoundClassRef->Properties.Volume);
		UE_LOG(LogTemp, Warning, TEXT("%f"), e.Value.SoundClassRef->Properties.Volume);

		RootObject->SetObjectField(keyString, SettingsObject);
	}

	FString outputString;
	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&outputString);
	FJsonSerializer::Serialize(RootObject.ToSharedRef(), writer);

	const FString SavePath = FPaths::ProjectSavedDir() + TEXT("SoundSettings.json");
	FFileHelper::SaveStringToFile(outputString, *SavePath);
}
