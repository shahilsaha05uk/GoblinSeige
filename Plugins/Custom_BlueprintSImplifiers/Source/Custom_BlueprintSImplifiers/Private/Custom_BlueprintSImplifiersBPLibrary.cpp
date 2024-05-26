// Copyright Epic Games, Inc. All Rights Reserved.

#include "Custom_BlueprintSImplifiersBPLibrary.h"

#include "Components/OverlaySlot.h"
#include "Components/UniformGridSlot.h"

UCustom_BlueprintSImplifiersBPLibrary::UCustom_BlueprintSImplifiersBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}


void UCustom_BlueprintSImplifiersBPLibrary::SetOverlayAlignment(UOverlaySlot* OverlayRef, EHorizontalAlignment HorizontalAlignment,
	EVerticalAlignment VerticalAlignment)
{
	OverlayRef->SetHorizontalAlignment(HorizontalAlignment);
	OverlayRef->SetVerticalAlignment(VerticalAlignment);
}

void UCustom_BlueprintSImplifiersBPLibrary::SetUniformGridAlignment(UUniformGridSlot* GridRef,
	EHorizontalAlignment HorizontalAlignment, EVerticalAlignment VerticalAlignment)
{
	GridRef->SetHorizontalAlignment(HorizontalAlignment);
	GridRef->SetVerticalAlignment(VerticalAlignment);
}
