#pragma once
#include "ParticleSystem/Particle.h"
#include <list>



class ParticleDrawer
{
public:
	void Initalize();

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void PreDraw();

	void addParticle(int ParticleNumber,int particleVolume, const std::string filePath, Vector3 Pos);

	void Reset(int ParticleNumber, Vector3 Pos);

	static const uint32_t kParticle = 20;

private:
	static const uint32_t kMaxParticle = 10;

	DirectXCommon* directX_ = nullptr;
	TextureManager* textureManager_ = nullptr;

	std::array<Particle, kMaxParticle> particles_;

	std::unique_ptr<ParticlePipeLine> Pipeline_;
};
