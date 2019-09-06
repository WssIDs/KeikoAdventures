// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class KeikoAdventures : ModuleRules
{
	public KeikoAdventures(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        //PublicIncludePaths.AddRange(
        //new string[] {
        //     "Public/Characters/",
        //     "Public/Gameplay/",
        //     "Public/UI/"
        //    // ... add public include paths required here ...
        //}
        //);

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "MoviePlayer", "APEXDESTRUCTION","VlcMedia" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        //PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
