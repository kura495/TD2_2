#pragma once
#include "ParticleSystem/Particle.h"
#include <array>

class ParticleDrawer
{
public:
	void Initalize(int particleVolume, const std::string filePath, Vector3 Pos);

	void Update();

	void Draw(const ViewProjection& viewProjection);


private:
	std::array<std::unique_ptr<Particle>,20> particle;
};
