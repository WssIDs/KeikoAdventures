// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class KeikoAdventuresTarget : TargetRules
{
	public KeikoAdventuresTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

        ExtraModuleNames.AddRange( new string[] { "KeikoAdventures" } );
	}
}
