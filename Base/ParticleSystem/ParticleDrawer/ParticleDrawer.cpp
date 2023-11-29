#include "ParticleDrawer.h"

void ParticleDrawer::Initalize()
{
	textureManager_ = TextureManager::GetInstance();
	directX_ = DirectXCommon::GetInstance();

	Pipeline_ = std::make_unique<ParticlePipeLine>();
	Pipeline_->Initalize();

}

void ParticleDrawer::Update()
{
	for (uint32_t Volume_i = 0; Volume_i < kMaxParticle; Volume_i++) {
		if (particles_[Volume_i].GetIsAlive()) {
			particles_[Volume_i].Update();
		}
	}
	
}

void ParticleDrawer::Draw(const ViewProjection& viewProjection)
{
	PreDraw();
	for (uint32_t Volume_i = 0; Volume_i < kMaxParticle; Volume_i++) {
		if (particles_[Volume_i].GetIsAlive()) {
			particles_[Volume_i].Draw(viewProjection);
		}
	}
}

void ParticleDrawer::PreDraw()
{
	directX_->GetcommandList()->SetGraphicsRootSignature(Pipeline_->GetPSO().rootSignature.Get());
	directX_->GetcommandList()->SetPipelineState(Pipeline_->GetPSO().graphicsPipelineState.Get());

}

void ParticleDrawer::addParticle(int ParticleNumber ,int particleVolume, const std::string filePath, Vector3 Pos)
{
	particles_.at(ParticleNumber).Initalize(particleVolume, filePath, Pos);
}

void ParticleDrawer::Reset(int ParticleNumber, Vector3 Pos)
{
	particles_.at(ParticleNumber).SetIsAlive(true);
	particles_.at(ParticleNumber).Reset(Pos);
}
