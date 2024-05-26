// Copyright Epic Games, Inc. All Rights Reserved.

#include "Custom_BlueprintSImplifiers.h"

#define LOCTEXT_NAMESPACE "FCustom_BlueprintSImplifiersModule"

void FCustom_BlueprintSImplifiersModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FCustom_BlueprintSImplifiersModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustom_BlueprintSImplifiersModule, Custom_BlueprintSImplifiers)