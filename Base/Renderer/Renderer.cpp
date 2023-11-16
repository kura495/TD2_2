#include "Renderer.h"

void Renderer::Initalize()
{
	//TODO : 削除予定
	//commandList = DirectXCommon::GetInstance()->GetcommandList();
	PSOManager_ = std::make_unique<PSOManager>();
	PSOManager_->Initalize();
}

void Renderer::Draw()
{
	DirectXCommon::GetInstance()->GetcommandList()->SetGraphicsRootSignature(PSOManager_->GetRootSignature().Get());
	DirectXCommon::GetInstance()->GetcommandList()->SetPipelineState(PSOManager_->GetPipelineState().Get());
}
