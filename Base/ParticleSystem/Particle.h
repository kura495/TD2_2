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

struct ParticleWVPData {
	Matrix4x4 matWorld; // ローカル → ワールド
	Vector3 velocity;
};

class Particle
{
public:

	void Initalize(int particleVolume);

	void Update();

	void PreDraw();

	void Draw(const ViewProjection& viewProjection);

private:
	//インスタンスの数
	const uint32_t kNumInstance = 10;

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
	WorldTransform InstancingDeta[10];
	ParticleWVPData* particleWVPData;

	//パーティクルの数
	int particleVolume_;
	//パーティクルの数分のtransform
	std::vector<WorldTransform> transform_;

	void CreateResources();
	void CreateSRV();

	Light* light_;

	std::unique_ptr<ParticlePipeLine> Pipeline_;

	D3D12_CPU_DESCRIPTOR_HANDLE instancingSRVHandleCPU;
	D3D12_GPU_DESCRIPTOR_HANDLE instancingSRVHandleGPU;

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index);
};

