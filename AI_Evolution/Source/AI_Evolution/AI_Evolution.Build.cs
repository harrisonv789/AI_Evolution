// FIT3094 ASSIGNMENT 3 - EVOLUTION
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
