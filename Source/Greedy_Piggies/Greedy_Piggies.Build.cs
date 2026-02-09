using UnrealBuildTool;

public class Greedy_Piggies : ModuleRules
{
    public Greedy_Piggies(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
    
        // We added "OnlineSubsystem" and "OnlineSubsystemSteam" to this list
        PublicDependencyModuleNames.AddRange(new string[] { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore", 
            "OnlineSubsystem", 
            "OnlineSubsystemSteam" 
        });

        PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}