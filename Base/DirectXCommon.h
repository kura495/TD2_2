﻿#pragma once
#include "Log.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#include "WinApp.h"
#include "Math_Structs.h"
#include <dxcapi.h>
#pragma comment(lib,"dxcompiler.lib")
#include <dxgidebug.h>
#pragma comment(lib,"dxguid.lib")
#include "externals/DirectXTex/d3dx12.h"
#include <wrl.h>

#include "PipeLineState/PipeLineTags.h"

struct PipelineStateObject {
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> graphicsPipelineState;
	Microsoft::WRL::ComPtr<ID3D12Resource>_peraResource;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>_peraRTVHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>_peraSRVHeap;
};

class DirectXCommon
{
public:
	static DirectXCommon* GetInstance();
	void Initialize(WinApp* winApp);

	void PreView();

	void PostView();

	void Release();
	
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInBytes);
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>
		CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);
	Microsoft::WRL::ComPtr<ID3D12Resource>
		CreateDepthStencilTextureResource(int32_t width, int32_t height);

#pragma region Getter	
	
	ID3D12GraphicsCommandList*GetcommandList()const { return commandList.Get(); }
	ID3D12Device* GetDevice()const { return device.Get(); }
	DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc()const { return swapChainDesc; }
	D3D12_DESCRIPTOR_HEAP_DESC GetrtvDescFormHeap()const { return rtvDescriptorHeap->GetDesc(); }D3D12_RENDER_TARGET_VIEW_DESC GetrtvDesc()const { return rtvDesc; }
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>
	 GetsrvDescriptorHeap()const { return srvDescriptorHeap.Get(); }
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetdsvDescriptorHeap() {
		return dsvDescriptorHeap.Get();
	}
	Microsoft::WRL::ComPtr<ID3D12Resource> GetswapChainResources()const { return swapChainResources[0]; }
#pragma endregion	

private:
	DirectXCommon() = default;
	~DirectXCommon() = default;
	DirectXCommon(const DirectXCommon& obj) = delete;
	DirectXCommon& operator=(const DirectXCommon& obj) = delete;

	WinApp* winApp_;
	HRESULT hr;

	D3D12_RESOURCE_BARRIER barrier{};
	Microsoft::WRL::ComPtr<IDXGIFactory7>dxgiFactory = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter4>useAdapter = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Device>device = nullptr;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue = nullptr;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator>commandAllocator = nullptr;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>commandList = nullptr;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	Microsoft::WRL::ComPtr<IDXGISwapChain4>swapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>rtvDescriptorHeap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>srvDescriptorHeap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>dsvDescriptorHeap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource>depthStencilResource = nullptr;
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	
	Microsoft::WRL::ComPtr<ID3D12Resource>swapChainResources[2] = { nullptr };
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];
	Microsoft::WRL::ComPtr<ID3D12Fence>fence = nullptr;
	uint64_t fenceValue = 0;
	HANDLE fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	D3D12_VIEWPORT viewport{};

	D3D12_RECT scissorRect{};
#ifdef _DEBUG
	Microsoft::WRL::ComPtr<ID3D12Debug1>debugController = nullptr;
#endif

//プライベート関数

	void MakeDXGIFactory();
	void MakeD3D12Device();
	void MakeCommandQueue();
	void MakeCommandAllocator();
	void MakeCommandList();
	void MakeSwapChain();
	void MakeDescriptorHeap();
	void MakeFence();

	void MakeViewport();
	void MakeScissor();
};


