// Copyright 2023 ChangHao Miao. All Rights Reserved.
#include "SimpleLogBlueprintlibrary.h"
#include "Engine.h"
#include "Kismet/KismetSystemLibrary.h"

USimpleLogBlueprintlibrary* USimpleLogBlueprintlibrary::GetSimpleLogSubSystem()
{
	USimpleLogBlueprintlibrary* self = Cast<USimpleLogBlueprintlibrary>(GEngine);
	if (!self)
	{
		USimpleLogBlueprintlibrary* SimpleLogBlueprintlibraryInstance = NewObject<USimpleLogBlueprintlibrary>();
		return SimpleLogBlueprintlibraryInstance;
	}
	return self;
}


void USimpleLogBlueprintlibrary::PrintNormal(UObject* LogObject, FString InString, bool ToScreen, float DurationTime)
{
	if (!LogObject)
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), *InString);
	}
	else
	{
		FString Content = UKismetSystemLibrary::GetObjectName(LogObject) + ":" + InString;
		UE_LOG(LogTemp, Log, TEXT("%s"), *Content);
	}
	//to screen
	if (ToScreen)
	{
		GEngine->AddOnScreenDebugMessage(-1, DurationTime, FColor::White, InString);
	}
}

void USimpleLogBlueprintlibrary::PrintWarning(UObject* LogObject, FString InString, bool ToScreen, float DurationTime)
{
	if (!LogObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *InString);
	}
	else
	{
		FString Content = UKismetSystemLibrary::GetObjectName(LogObject) + ":" + InString;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Content);
	}
	//to screen
	if (ToScreen)
	{
		GEngine->AddOnScreenDebugMessage(-1, DurationTime, FColor::Yellow, InString);
	}
}

void USimpleLogBlueprintlibrary::PrintError(UObject* LogObject, FString InString, bool ToScreen, float DurationTime)
{
	//log 
	if (!LogObject)
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *InString);
	}
	else
	{
		FString Content = UKismetSystemLibrary::GetObjectName(LogObject) + ":" + InString;
		UE_LOG(LogTemp, Error, TEXT("%s"), *Content);
	}
	//to screen
	if (ToScreen)
	{
		GEngine->AddOnScreenDebugMessage(-1, DurationTime, FColor::Red, InString);
	}
}
