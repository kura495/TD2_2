#pragma once

#include <map>

#include "Base/DirectXCommon.h"

#include "PipelineState/Standard/Standard.h"
#include "PipelineState/MotionBlur/MotionBlur.h"

class PSOManager
{
public:
	static PSOManager* GetInstance();
	
	void Initalize();
	//void Update();
	//void Draw();

	Microsoft::WRL::ComPtr<ID3D12RootSignature> GetRootSignature(PipelineType Type) { return Pipeline_[Type].rootSignature.Get(); }
	Microsoft::WRL::ComPtr<ID3D12PipelineState> GetPipelineState(PipelineType Type) { return Pipeline_[Type].graphicsPipelineState.Get(); }
	Microsoft::WRL::ComPtr<ID3D12Resource> GetRenderTarget(PipelineType Type) { return Pipeline_[Type]._peraResource.Get(); }
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetRTVHeap(PipelineType Type) {
		return Pipeline_[Type]._peraRTVHeap.Get();
	};
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetSRVHeap(PipelineType Type) { return Pipeline_[Type]._peraSRVHeap.Get();
	};

	void AddPipeline(PipelineStateObject Pipeline, PipelineType Type) {
		Pipeline_[Type] = Pipeline;
	}

private:
	PSOManager() = default;
	~PSOManager() = default;
	PSOManager(const PSOManager& obj) = delete;
	PSOManager& operator=(const PSOManager& obj) = delete;

	std::map<PipelineType,PipelineStateObject> Pipeline_;

};
