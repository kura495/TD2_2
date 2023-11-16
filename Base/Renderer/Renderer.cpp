#include "Renderer.h"

void Renderer::Initalize()
{
	commandList = DirectXCommon::GetInstance()->GetcommandList();
	PSOManager_ = std::make_unique<PSOManager>();
	PSOManager_->Initalize();
}

void Renderer::Draw()
{
	commandList->SetGraphicsRootSignature(PSOManager_->GetRootSignature().Get());
	commandList->SetPipelineState(PSOManager_->GetPipelineState().Get());
}
