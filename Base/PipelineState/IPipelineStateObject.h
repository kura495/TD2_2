#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#include <dxcapi.h>
#pragma comment(lib,"dxcompiler.lib")
#include <dxgidebug.h>
#pragma comment(lib,"dxguid.lib")
#include "externals/DirectXTex/d3dx12.h"
#include <wrl.h>

#include "Base/DirectXCommon.h"

class IPipelineStateObject
{
public:

	virtual ~IPipelineStateObject();
	virtual void ShaderCompile() = 0;
	virtual void CreateRootSignature() = 0;
	virtual void CreateInputLayOut() = 0;
	virtual void CreateBlendState() = 0;
	virtual void CreateRasterizarState() = 0;
	virtual void CreatePipelineStateObject() = 0;

protected:
	HRESULT hr;

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
