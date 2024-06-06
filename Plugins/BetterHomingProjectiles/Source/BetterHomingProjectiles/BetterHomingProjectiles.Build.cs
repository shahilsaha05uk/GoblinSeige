// Copyright 2023 Harlan Cox. All Rights Reserved.

using UnrealBuildTool;

public class BetterHomingProjectiles : ModuleRules
{
	public BetterHomingProjectiles(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine"
			}
		);
	}
}
