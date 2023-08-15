#include "MyBlueprintFunctionLibrary.h"

#include "Modules/ModuleManager.h"
#include "BradLearnsUnreal.h"

void UMyBlueprintFunctionLibrary::PrintText(FString TextToPrint)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TextToPrint);
}

void UMyBlueprintFunctionLibrary::PrintModuleIsLoaded()
{
	bool loaded = FModuleManager::Get().IsModuleLoaded("BradLearnsUnreal");
	FString text = loaded ? TEXT("loaded") : TEXT("not loaded");
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, text);
}