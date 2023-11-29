#pragma once
#include "ParticleSystem/Particle.h"
#include <list>



class ParticleDrawer
{
public:
	void Initalize(int particleVolume, const std::string filePath, Vector3 Pos);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void PreDraw();

	static const uint32_t kParticle = 20;

private:
	DirectXCommon* directX_ = nullptr;
	TextureManager* textureManager_ = nullptr;

	std::list<Particle*> particles_;

	std::unique_ptr<ParticlePipeLine> Pipeline_;
};
