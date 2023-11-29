#include "ParticleDrawer.h"

void ParticleDrawer::Initalize(int particleVolume, const std::string filePath, Vector3 Pos)
{
	textureManager_ = TextureManager::GetInstance();
	directX_ = DirectXCommon::GetInstance();

	Pipeline_ = std::make_unique<ParticlePipeLine>();
	Pipeline_->Initalize();

}

void ParticleDrawer::Update()
{
	if()
	
}

void ParticleDrawer::Draw(const ViewProjection& viewProjection)
{
	directX_->GetcommandList()->SetGraphicsRootSignature(Pipeline_->GetPSO().rootSignature.Get());
	directX_->GetcommandList()->SetPipelineState(Pipeline_->GetPSO().graphicsPipelineState.Get());
}
