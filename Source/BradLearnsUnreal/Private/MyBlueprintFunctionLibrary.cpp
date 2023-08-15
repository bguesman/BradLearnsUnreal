#include "MyBlueprintFunctionLibrary.h"

void UMyBlueprintFunctionLibrary::PrintText(FString TextToPrint)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TextToPrint);
}