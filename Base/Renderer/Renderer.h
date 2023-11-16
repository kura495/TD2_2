#pragma once

#include "Base/DirectXCommon.h"
#include "Base/Manager/PSOManager.h"

class Renderer
{
public:
	void Initalize();
	//void Update();
	void Draw();

private:
	//TODO : 削除予定
	//Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>commandList = nullptr;
	std::unique_ptr<PSOManager> PSOManager_ = nullptr;
};
