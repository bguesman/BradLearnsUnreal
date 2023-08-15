#pragma once

#include "CoreMinimal.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * @brief Example of a library of functions that can be accessed
 * from blueprints.
 * 
 * Basically, you just make static functions in a blueprint library
 * class.
 */
UCLASS(Blueprintable)
class UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
  GENERATED_BODY()

public:
  UFUNCTION(BlueprintCallable, category = "MyBlueprintFunctionLibrary")
  static void PrintText(FString TextToPrint);

  UFUNCTION(BlueprintCallable, category = "MyBlueprintFunctionLibrary")
  static void PrintModuleIsLoaded();
};