#pragma once

#include "SimpleFog.h"
#include "SceneViewExtension.h"

class BRADLEARNSUNREAL_API FSimpleFogSceneViewExtension : public FSceneViewExtensionBase
{
  
public:
  FSimpleFogSceneViewExtension(const FAutoRegister& AutoRegister, ASimpleFog* simpleFog);

  // FSceneViewExtension interface
  virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override {};
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override {};
	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override {};
	virtual void PreRenderViewFamily_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneViewFamily& InViewFamily) override {};
	virtual void PreRenderView_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneView& InView) override {};
	virtual void PostRenderBasePass_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneView& InView) override {};
	virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs) override;

private:
	ASimpleFog* simpleFog;

};