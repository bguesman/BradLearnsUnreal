#include "SimpleFogSceneViewExtension.h"
#include "SimpleFog.h"
#include "MyShaders.h"
#include "Kismet/GameplayStatics.h"

#include "PixelShaderUtils.h"
#include "PostProcess/PostProcessing.h"

FSimpleFogSceneViewExtension::FSimpleFogSceneViewExtension(const FAutoRegister& AutoRegister, UWorld* InWorld) 
	: FWorldSceneViewExtension(AutoRegister, InWorld)
{
}

// Yoinked from Engine\Plugins\Experimental\ColorCorrectRegions\Source\ColorCorrectRegions\Private\ColorCorrectRegionsSceneViewExtension.cpp
// This is how it appears in Unreal 5.0.3 - in UE4 it uses FVector2D instead of FVector2f but is otherwise identical
FScreenPassTextureViewportParameters GetTextureViewportParameters(const FScreenPassTextureViewport& InViewport) {

	// BRAD NOTE: even though we borrow the UE parameter struct for the viewport, we still actually set it all up ourselves
	// with this function. I.e. we aren't really using bound shader globals, we're just borrowing the type.

	const FVector2f Extent(InViewport.Extent);
	const FVector2f ViewportMin(InViewport.Rect.Min.X, InViewport.Rect.Min.Y);
	const FVector2f ViewportMax(InViewport.Rect.Max.X, InViewport.Rect.Max.Y);
	const FVector2f ViewportSize = ViewportMax - ViewportMin;

	FScreenPassTextureViewportParameters Parameters;

	if (!InViewport.IsEmpty()) {
		Parameters.Extent = FVector2f(Extent);
		Parameters.ExtentInverse = FVector2f(1.0f / Extent.X, 1.0f / Extent.Y);

		Parameters.ScreenPosToViewportScale = FVector2f(0.5f, -0.5f) * ViewportSize;	
		Parameters.ScreenPosToViewportBias = (0.5f * ViewportSize) + ViewportMin;	

		Parameters.ViewportMin = InViewport.Rect.Min;
		Parameters.ViewportMax = InViewport.Rect.Max;

		Parameters.ViewportSize = ViewportSize;
		Parameters.ViewportSizeInverse = FVector2f(1.0f / Parameters.ViewportSize.X, 1.0f / Parameters.ViewportSize.Y);

		Parameters.UVViewportMin = ViewportMin * Parameters.ExtentInverse;
		Parameters.UVViewportMax = ViewportMax * Parameters.ExtentInverse;

		Parameters.UVViewportSize = Parameters.UVViewportMax - Parameters.UVViewportMin;
		Parameters.UVViewportSizeInverse = FVector2f(1.0f / Parameters.UVViewportSize.X, 1.0f / Parameters.UVViewportSize.Y);

		Parameters.UVViewportBilinearMin = Parameters.UVViewportMin + 0.5f * Parameters.ExtentInverse;
		Parameters.UVViewportBilinearMax = Parameters.UVViewportMax - 0.5f * Parameters.ExtentInverse;
	}

	return Parameters;
}

void FSimpleFogSceneViewExtension::SetupViewFamily(FSceneViewFamily& InViewFamily)
{
	// All world setup has to take place in a function not suffixed _RenderThread
	// You can't access the world in that thread
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASimpleFog::StaticClass(), fogsInScene);
}

void FSimpleFogSceneViewExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs)
{
	if (fogsInScene.Num() == 0)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No fog objects found in world");
		}
		return;
	}

	ASimpleFog* simpleFog = (ASimpleFog*) fogsInScene[0];

	checkSlow(View.bIsViewInfo); // can't do dynamic_cast because FViewInfo doesn't have any virtual functions.
	const FIntRect Viewport = static_cast<const FViewInfo&>(View).ViewRect;
	FScreenPassTexture SceneColor((*Inputs.SceneTextures)->SceneColorTexture, Viewport);
	FScreenPassTexture SceneDepth((*Inputs.SceneTextures)->SceneDepthTexture, Viewport);
	FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);

	RDG_EVENT_SCOPE(GraphBuilder, "Red Scene View Extension Render Pass");

	// Viewport parameters
	const FScreenPassTextureViewport SceneColorTextureViewport(SceneColor);
	const FScreenPassTextureViewportParameters SceneTextureViewportParams = GetTextureViewportParameters(SceneColorTextureViewport);


	// Shader setup
	TShaderMapRef<FRecolorShaderPS> RecolorPixelShader(GlobalShaderMap);
	FRecolorShaderPS::FParameters* RecolorParameters = GraphBuilder.AllocParameters<FRecolorShaderPS::FParameters>();
	RecolorParameters->SceneColor = SceneColor.Texture;
	RecolorParameters->SceneDepth = SceneDepth.Texture;
	RecolorParameters->InputSampler = TStaticSamplerState<SF_Point, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI();
	RecolorParameters->Scattering = simpleFog->Scattering;
	RecolorParameters->Extinction = simpleFog->Extinction;
	RecolorParameters->MaxDistAndDensity = FLinearColor(simpleFog->MaxDistance, simpleFog->Density, 0, 0);
	RecolorParameters->ViewParams = SceneTextureViewportParams;
	RecolorParameters->RenderTargets[0] = FRenderTargetBinding(SceneColor.Texture, ERenderTargetLoadAction::ELoad);

	FPixelShaderUtils::AddFullscreenPass(
		GraphBuilder,
		GlobalShaderMap,
		FRDGEventName(TEXT("Recolor")),
		RecolorPixelShader,
		RecolorParameters,
		Viewport);

}