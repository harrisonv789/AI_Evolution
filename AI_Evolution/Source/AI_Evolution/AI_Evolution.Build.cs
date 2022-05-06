// FIT3094 ASSIGNMENT 2 - GOAL PLANNING 
// Author: Harrison Verrios


using UnrealBuildTool;

public class AI_Evolution : ModuleRules
{
	public AI_Evolution(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Niagara" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
