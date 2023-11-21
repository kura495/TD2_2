#pragma once

#include "Base/PipelineState/IPipelineStateObject.h"
#include "Base/Manager/PSOManager.h"


class MotionBlur : public IPipelineStateObject
{
public:

	void Initalize()override;
	void ShaderCompile() override;
	void CreateRootSignature() override;
	void CreateInputLayOut() override;
	void CreateBlendState() override;
	void CreateRasterizarState() override;
	void CreatePipelineStateObject() override;

	void CreateHeap();

private:
	DirectXCommon* directX_;

};