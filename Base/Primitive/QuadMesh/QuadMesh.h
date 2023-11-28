#pragma once
#include "DirectXCommon.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Transform.h"
#include "VertexData.h"
#include "Material.h"
#include "MatrixCalc.h"

class QuadMesh
{
public:
	void Initialize();
	void Draw();

private:
	DirectXCommon* directX_ = nullptr;
	TextureManager* textureManager_ = nullptr;

	//�o�[�e�b�N�X���\�[�X
	Microsoft::WRL::ComPtr<ID3D12Resource>vertexResource = nullptr;
	VertexData* vertexData = nullptr;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource = nullptr;
	Material* materialData = nullptr;

	void MakeVertexBufferView();


};