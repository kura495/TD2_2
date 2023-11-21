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
	void ChengeRenderTarget();

private:
	DirectXCommon* directX_;

	Microsoft::WRL::ComPtr<ID3D12Resource>_peraResource;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>_peraRTVHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>_peraSRVHeap;
};