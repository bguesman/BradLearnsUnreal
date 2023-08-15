#pragma once

#include "GlobalShader.h"
#include "ScreenPass.h"

BEGIN_SHADER_PARAMETER_STRUCT(FRecolorShaderParameters, )
	SHADER_PARAMETER_RDG_TEXTURE(Texture2D, SceneColor)
	SHADER_PARAMETER_SAMPLER(SamplerState, InputSampler)
	SHADER_PARAMETER_STRUCT(FScreenPassTextureViewportParameters, ViewParams)
	RENDER_TARGET_BINDING_SLOTS()
END_SHADER_PARAMETER_STRUCT()

class FRecolorShaderPS : public FGlobalShader {
public:
	DECLARE_EXPORTED_SHADER_TYPE(FRecolorShaderPS, Global, );
	using FParameters = FRecolorShaderParameters;
	SHADER_USE_PARAMETER_STRUCT(FRecolorShaderPS, FGlobalShader);
};