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
	particles_.remove_if([&](Particle* particle) {
		if (particle->GetIsAlive()) {
			return false;
		}
		else {
			delete particle;
			return true;
		}
	});
	for (Particle* particle : particles_) {
		particle->Update();
	}
	
}

void ParticleDrawer::Draw(const ViewProjection& viewProjection)
{
	PreDraw();
	for (Particle* particle : particles_) {
		particle->Draw(viewProjection);
	}
}

void ParticleDrawer::PreDraw()
{
	directX_->GetcommandList()->SetGraphicsRootSignature(Pipeline_->GetPSO().rootSignature.Get());
	directX_->GetcommandList()->SetPipelineState(Pipeline_->GetPSO().graphicsPipelineState.Get());

}

void ParticleDrawer::addParticle(int particleVolume, const std::string filePath, Vector3 Pos)
{
	Particle* particle = new Particle();
	particle->Initalize(particleVolume, filePath, Pos);
	particles_.push_back(particle);
}
