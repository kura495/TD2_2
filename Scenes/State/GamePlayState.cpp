#include "Scenes/State/GamePlayState.h"

void GamePlayState::Initialize()
{
	//基本機能生成
	input = Input::GetInstance();
	audio = Audio::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	light_ = Light::GetInstance();

	DirectX_ = DirectXCommon::GetInstance();


}

void GamePlayState::Update()
{

}

void GamePlayState::Draw()
{
	//3Dモデル描画ここから

	//3Dモデル描画ここまで	

	//Sprite描画ここから


	//Sprite描画ここまで
	
	//描画ここまで
}
