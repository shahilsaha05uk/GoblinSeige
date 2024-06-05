// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TowerDefenceGame : ModuleRules
{
	public TowerDefenceGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Json", "JsonUtilities", "Custom_BlueprintSImplifiers", "Niagara", "AIModule", "GameplayTasks"});

		PrivateDependencyModuleNames.AddRange(new string[] { "EnhancedInput"});

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
