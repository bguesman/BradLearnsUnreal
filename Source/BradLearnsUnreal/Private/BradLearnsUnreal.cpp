// Copyright Epic Games, Inc. All Rights Reserved.

#include "BradLearnsUnreal.h"
#include "ShaderCore.h"

#define LOCTEXT_NAMESPACE "FBradLearnsUnrealModule"

void FBradLearnsUnrealModule::StartupModule()
{
	// This maps our shaders into a virtual directory called /BradLearnsUnreal so that we can
	// use that to specify them in the IMPLEMENT_SHADER_TYPE macro
	FString BaseDir = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("BradLearnsUnreal"));
	FString ModuleShaderDir = FPaths::Combine(BaseDir, TEXT("Source/BradLearnsUnreal/Shaders"));
	// TODO [BRAD]: this causes an assertion crash because it's already been added if you
	// try to recompile it in editor
	if (!AllShaderSourceDirectoryMappings().Contains(TEXT("/BradLearnsUnreal")))
	{
		AddShaderSourceDirectoryMapping(TEXT("/BradLearnsUnreal"), ModuleShaderDir);
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Loading module Brad Learns Unreal");
	}
}

void FBradLearnsUnrealModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBradLearnsUnrealModule, BradLearnsUnreal)