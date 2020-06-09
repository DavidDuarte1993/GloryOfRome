using UnrealBuildTool;
using System.Collections.Generic;

public class GladiatorArenaTarget : TargetRules
{
	public GladiatorArenaTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "GladiatorArena" } );
	}
}
