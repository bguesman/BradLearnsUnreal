#include "RedSceneViewExtension.h"

FRedSceneViewExtension::FRedSceneViewExtension(const FAutoRegister& AutoRegister) : FSceneViewExtensionBase(AutoRegister) 
{
}

void FRedSceneViewExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& inputs)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Running red scene view ext");
}