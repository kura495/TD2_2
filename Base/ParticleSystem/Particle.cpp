#include "Particle.h"

void Particle::Initalize(int particleVolume)
{
	light_ = Light::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	directX_ = DirectXCommon::GetInstance();

	modelData.vertices.push_back({ .position = { -1.0f,1.0f,0.0f,1.0f },.texcoord = {0.0f,0.0f},.normal = {0.0f,0.0f,1.0f} });//左上
	modelData.vertices.push_back({ .position = {1.0f,1.0f,0.0f,1.0f}, .texcoord = {1.0f,0.0f},.normal = {0.0f,0.0f,1.0f} });//右上
	modelData.vertices.push_back({ .position = {-1.0f,-1.0f,0.0f,1.0f}, .texcoord = {0.0f,1.0f},.normal = {0.0f,0.0f,1.0f} });//左下
	modelData.vertices.push_back({ .position = {-1.0f,-1.0f,0.0f,1.0f},  .texcoord = {0.0f,1.0f},.normal = {0.0f,0.0f,1.0f} });//左下
	modelData.vertices.push_back({ .position = {1.0f,1.0f,0.0f,1.0f}, .texcoord = {1.0f,0.0f},.normal = {0.0f,0.0f,1.0f} });//右上
	modelData.vertices.push_back({ .position = {1.0f,-1.0f,0.0f,1.0f},.texcoord = {1.0f,1.0f},.normal = {0.0f,0.0f,1.0f} });//右下
	modelData.material.textureFilePath = "resources/fence.png";
	int Texture = textureManager_->LoadTexture(modelData.material.textureFilePath);
	int Texture2 = textureManager_->LoadTexture(modelData.material.textureFilePath);
	modelData.TextureIndex = Texture;
	Texture = Texture2;
	particleVolume_ = particleVolume;

	CreateResources();
	CreateSRV();	
	for (int Volume_i = 0; Volume_i < particleVolume_; Volume_i++) {
		
		InstancingDeta[Volume_i].translation_ = { Volume_i * 0.1f,Volume_i * 0.1f, Volume_i * 0.1f };
		InstancingDeta[Volume_i].matWorld_ = MakeAffineMatrix( InstancingDeta[Volume_i].scale_, InstancingDeta[Volume_i].quaternion,InstancingDeta[Volume_i].translation_);
	}


	materialData->enableLighting = false;
	materialData->color = { 1.0f,1.0f,1.0f,1.0f };
	materialData->uvTransform = CreateIdentity4x4();

	Pipeline_ = std::make_unique<ParticlePipeLine>();
	Pipeline_->Initalize();

}

void Particle::Update()
{

}

void Particle::PreDraw()
{
	directX_->GetcommandList()->SetGraphicsRootSignature(Pipeline_->GetPSO().rootSignature.Get());
	directX_->GetcommandList()->SetPipelineState(Pipeline_->GetPSO().graphicsPipelineState.Get());
}

void Particle::Draw(const ViewProjection& viewProjection)
{
	directX_->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//頂点
	directX_->GetcommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);

	//ViewProjection
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(2, viewProjection.constBuff_->GetGPUVirtualAddress());
	//色とuvTransform
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	//テクスチャ
	directX_->GetcommandList()->SetGraphicsRootDescriptorTable(3, textureManager_->GetGPUHandle(modelData.TextureIndex));
	Matrix4x4 ViewProj = Multiply(viewProjection.matView, viewProjection.matProjection);
	for (int Volume_i = 0; Volume_i < particleVolume_; ++Volume_i) {
		constMapWVPDeta[Volume_i].matWorld = Multiply(InstancingDeta[Volume_i].matWorld_, ViewProj);
	}

	//インスタンシング用WVP
	directX_->GetcommandList()->SetGraphicsRootDescriptorTable(1, instancingSRVHandleGPU);

	directX_->GetcommandList()->DrawInstanced(6, particleVolume_, 0, 0);
}

void Particle::CreateResources()
{
	//CreateVertexResource
	vertexResource = directX_->CreateBufferResource(sizeof(VertexData) * modelData.vertices.size());
	//CreateVertexbufferView
	vertexBufferView.BufferLocation = vertexResource.Get()->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = UINT(sizeof(VertexData) * modelData.vertices.size());
	vertexBufferView.StrideInBytes = sizeof(VertexData);
	//maping vertexResource
	vertexResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	std::memcpy(vertexData, modelData.vertices.data(), sizeof(VertexData) * modelData.vertices.size());
	//CreatematerialResource
	materialResource = directX_->CreateBufferResource(sizeof(Material));
	//maping materialResource
	materialResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	//Create InstancingResources
	InstancingResource = directX_->CreateBufferResource(sizeof(ParticleWVPData)* kNumInstance);
	//maping InstancingResources
	InstancingResource->Map(0,nullptr,reinterpret_cast<void**>(&constMapWVPDeta));
	
}

void Particle::CreateSRV()
{
	uint32_t descriptorSizeSRV = directX_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	D3D12_SHADER_RESOURCE_VIEW_DESC instancingSrvDesc{};
	instancingSrvDesc.Format = DXGI_FORMAT_UNKNOWN;
	instancingSrvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	instancingSrvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	instancingSrvDesc.Buffer.FirstElement = 0;
	instancingSrvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	instancingSrvDesc.Buffer.NumElements = kNumInstance;
	instancingSrvDesc.Buffer.StructureByteStride = sizeof(ParticleWVPData);

	instancingSRVHandleCPU = GetCPUDescriptorHandle(directX_->GetsrvDescriptorHeap(), descriptorSizeSRV, 3);
	instancingSRVHandleGPU = GetGPUDescriptorHandle(directX_->GetsrvDescriptorHeap(), descriptorSizeSRV, 3);
	directX_->GetDevice()->CreateShaderResourceView(InstancingResource.Get(),&instancingSrvDesc, instancingSRVHandleCPU);
}

D3D12_CPU_DESCRIPTOR_HANDLE Particle::GetCPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index)
{
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	handleCPU.ptr += (descriptorSize * index);
	return handleCPU;
}

D3D12_GPU_DESCRIPTOR_HANDLE Particle::GetGPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index)
{
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
	handleGPU.ptr += (descriptorSize * index);
	return handleGPU;
}
