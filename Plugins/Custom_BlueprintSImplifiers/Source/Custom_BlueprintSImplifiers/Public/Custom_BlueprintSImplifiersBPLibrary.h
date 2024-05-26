// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Custom_BlueprintSImplifiersBPLibrary.generated.h"

UCLASS()
class UCustom_BlueprintSImplifiersBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Overlay Alignment", Keywords = "Fixer"), Category = "Custom_BlueprintSImplifiersTesting")
	static void SetOverlayAlignment(class UOverlaySlot* OverlayRef, EHorizontalAlignment HorizontalAlignment, EVerticalAlignment VerticalAlignment);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Uniform Grid Alignment", Keywords = "Fixer"), Category = "Custom_BlueprintSImplifiersTesting")
	static void SetUniformGridAlignment(class UUniformGridSlot* GridRef, EHorizontalAlignment HorizontalAlignment, EVerticalAlignment VerticalAlignment);
};
