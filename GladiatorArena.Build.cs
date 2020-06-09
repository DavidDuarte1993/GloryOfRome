using UnrealBuildTool;

public class GladiatorArena : ModuleRules
{
	public GladiatorArena(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine",
            "InputCore", "AIModule" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
