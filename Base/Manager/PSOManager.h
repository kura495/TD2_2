#pragma once

#include "Base/DirectXCommon.h"

class PSOManager
{
public:

	
	void Initalize();
	//void Update();
	//void Draw();

	Microsoft::WRL::ComPtr<ID3D12RootSignature> GetRootSignature() { return rootSignature.Get(); }
	Microsoft::WRL::ComPtr<ID3D12PipelineState> GetPipelineState() { return graphicsPipelineState.Get(); }

private:
	
};
