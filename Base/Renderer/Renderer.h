#pragma once

#include "Base/DirectXCommon.h"
#include "Manager/PSOManager.h"
#include "PipelineState/Standard/Standard.h"

class Renderer
{
public:

	static Renderer* GetInstance();

	void Initalize();
	//void Update();
	void Draw(PipelineType Type);

	void ChengeRenderTarget(PipelineType Type);

private:
	Renderer() = default;
	~Renderer() = default;
	Renderer(const Renderer& obj) = delete;
	Renderer& operator=(const Renderer& obj) = delete;

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>commandList = nullptr;
	PSOManager* PSOManager_ = nullptr;
	DirectXCommon* directX_;
};
