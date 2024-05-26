// Copyright 2023 ChangHao Miao. All Rights Reserved.
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SimpleLogBlueprintlibrary.generated.h"

UCLASS(Blueprintable)
class USimpleLogBlueprintlibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	//Get this public class,However you can call this node
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(DisplayName = "SimpleLogSubSystem"), Category="SimpleLog")
	static USimpleLogBlueprintlibrary* GetSimpleLogSubSystem();

	//Normal Log,Color:White
	UFUNCTION(BlueprintCallable, Category="SimpleLog")
	static void PrintNormal(UObject* LogObject, FString InString, bool ToScreen = true, float DurationTime = 3);

	//Warning Log,Color:Yellow
	UFUNCTION(BlueprintCallable, Category="SimpleLog")
	static void PrintWarning(UObject* LogObject, FString InString, bool ToScreen = true, float DurationTime = 3);

	//Error Log,Color:Red
	UFUNCTION(BlueprintCallable, Category="SimpleLog")
	static void PrintError(UObject* LogObject, FString InString, bool ToScreen = true, float DurationTime = 3);
};
