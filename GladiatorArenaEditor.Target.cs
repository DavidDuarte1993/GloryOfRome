
using UnrealBuildTool;
using System.Collections.Generic;

public class GladiatorArenaEditorTarget : TargetRules
{
	public GladiatorArenaEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "GladiatorArena" } );
	}
}
