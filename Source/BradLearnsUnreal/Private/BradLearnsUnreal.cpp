// Copyright Epic Games, Inc. All Rights Reserved.

#include "BradLearnsUnreal.h"

#define LOCTEXT_NAMESPACE "FBradLearnsUnrealModule"

void FBradLearnsUnrealModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogTemp, Warning, TEXT("Brad Learns Unreal Module Startup"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Brad Learns Unreal Module Startup"));
}

void FBradLearnsUnrealModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FBradLearnsUnrealModule::PrintToScreen()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Brad Learns Unreal Module Startup"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBradLearnsUnrealModule, BradLearnsUnreal)