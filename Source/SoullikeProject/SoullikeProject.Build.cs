// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SoullikeProject : ModuleRules
{
	public SoullikeProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;


        PublicIncludePaths.AddRange(
            new string[] {
                "SoullikeProject"
            }
        );

        //PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput" });

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "GameplayAbilities",
            "GameplayTasks",
            "GameplayTags",
            //"ModularGameplayActors",
            "EnhancedInput",
            "AIModule", "GameplayTasks", "UMG", "Niagara","Cascade",
            "NavigationSystem"
        });


        PrivateDependencyModuleNames.AddRange(new string[] {
            "GameFeatures",
            "RHI",
            "RenderCore",
            "SlateCore",
            "NetCore",
            "ModularGameplay",
        });

        PublicIncludePaths.Add(ModuleDirectory);
    }
}
