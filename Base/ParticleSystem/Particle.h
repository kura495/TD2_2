#pragma once

#include "DirectXCommon.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Math/MatrixCalc.h"
#include "ModelData.h"
#include "Base/Light.h"

#include "Utility/ImGuiManager.h"

#include "PipeLine/ParticlePipeLine.h"

class Particle
{
public:

	void Initalize(int particleVolume);

	void Update();

	void PreDraw();

	void Draw(const ViewProjection& viewProjection);

private:
	ModelData modelData;

	DirectXCommon* directX_ = nullptr;
	TextureManager* textureManager_ = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource>vertexResource = nullptr;
	VertexData* vertexData = nullptr;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource = nullptr;
	Material* materialData = nullptr;
	//Instancing用にTransformMatrixを複数格納できるResourcesを作る
	Microsoft::WRL::ComPtr<ID3D12Resource> InstancingResource = nullptr;
	WorldTransform* InstancingData = nullptr;

	//パーティクルの数
	int particleVolume_;
	//パーティクルの数分のtransform
	std::vector<WorldTransform> transform_;

	void CreateResources();

	Light* light_;

	std::unique_ptr<ParticlePipeLine> Pipeline_;
};

