#include "Renderer.h"

Renderer* Renderer::GetInstance()
{
	static Renderer instance;
	return &instance;
}

void Renderer::Initalize()
{
	commandList = DirectXCommon::GetInstance()->GetcommandList();
	PSOManager_ = PSOManager::GetInstance();
	PSOManager_->Initalize();
	directX_ = DirectXCommon::GetInstance();

}

void Renderer::Draw(PipelineType Type)
{
	commandList->SetGraphicsRootSignature(PSOManager_->GetRootSignature(Type).Get());
	commandList->SetPipelineState(PSOManager_->GetPipelineState(Type).Get());
}

void Renderer::ChengeRenderTarget(PipelineType Type)
{
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapPointer = PSOManager_->GetRTVHeap(Type)->GetCPUDescriptorHandleForHeapStart();
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = directX_->GetdsvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
		D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(PSOManager_->GetRenderTarget(Type).Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET);
		directX_->GetcommandList()->OMSetRenderTargets(1, &rtvHeapPointer, false, &dsvHandle);
		directX_->GetcommandList()->ResourceBarrier(1, &barrier);
}

