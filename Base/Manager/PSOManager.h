#pragma once

#include "Base/DirectXCommon.h"

class PSOManager
{
public:
	
	void Initalize();
	//void Update();
	//void Draw();

	Microsoft::WRL::ComPtr<ID3D12RootSignature> GetRootSignature() { return rootSignature.Get(); }
	Microsoft::WRL::ComPtr<ID3D12PipelineState> GetPipelineState() { return graphicsPipelineState.Get(); }

private:
	void MakeDXC();
	void MakeShaderCompile();
	IDxcBlob* CompileShader(const std::wstring& filePath, const wchar_t* profile);
	//PSO
	void MakeRootSignature();
	void MakeInputLayOut();
	void MakeBlendState();
	void MakeRasterizarState();
	void MakePipelineStateObject();

	HRESULT hr;

	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;

	IDxcBlobUtf8* shaderError = nullptr;

	IDxcBlob* shaderBlob = nullptr;

	IDxcBlob* vertexShaderBlob = nullptr;
	IDxcBlob* pixelShaderBlob = nullptr;

	Microsoft::WRL::ComPtr<ID3D12RootSignature>rootSignature = nullptr;
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	D3D12_INPUT_ELEMENT_DESC inputElementDescs[3] = {};
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};

	D3D12_BLEND_DESC blendDesc{};

	D3D12_RASTERIZER_DESC rasterizerDesc{};

	Microsoft::WRL::ComPtr<ID3D12PipelineState>graphicsPipelineState = nullptr;

};
