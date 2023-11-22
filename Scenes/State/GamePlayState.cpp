#include "Scenes/State/GamePlayState.h"

void GamePlayState::Initialize()
{
	input = Input::GetInstance();
	audio = Audio::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	light_ = Light::GetInstance();
	light_->Initialize();
	DirectX_ = DirectXCommon::GetInstance();

	viewProjection_.Initialize();


	renderer_ = Renderer::GetInstance();

	particle = std::make_unique<Particle>();
	particle->Initalize(10);
}

void GamePlayState::Update()
{
	viewProjection_.UpdateMatrix();

}

void GamePlayState::Draw()
{
	//3Dモデル描画ここから
	
	particle->PreDraw();
	particle->Draw(viewProjection_);

	//3Dモデル描画ここまで	

	//Sprite描画ここから


	//Sprite描画ここまで
	
	//描画ここまで
}
