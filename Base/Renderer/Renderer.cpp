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

}

void Renderer::Draw(PipelineType Type)
{
	commandList->SetGraphicsRootSignature(PSOManager_->GetRootSignature(Type).Get());
	commandList->SetPipelineState(PSOManager_->GetPipelineState(Type).Get());
}
