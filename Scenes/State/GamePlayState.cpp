#include "Scenes/State/GamePlayState.h"

void GamePlayState::Initialize()
{
	input = Input::GetInstance();
	audio = Audio::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	light_ = Light::GetInstance();

	DirectX_ = DirectXCommon::GetInstance();

	collisionManager_ = std::make_unique<CollisionManager>();

	viewProjection_.Initialize();
	worldTransform_.Initialize();

	groundModel_.reset(Model::CreateModelFromObj("resources/float_Head", "float_Head.obj"));

	ground_ = std::make_unique<Ground>();
	ground_->Initialize(groundModel_.get(), { 0.0f,0.0f,0.0f });
}

void GamePlayState::Update()
{
	ground_->Update();

	viewProjection_.UpdateMatrix();

	collisionManager_->AddBoxCollider(ground_.get());

	ImGui::Begin("Play");

	ImGui::End();
}

void GamePlayState::Draw()
{
	//3Dモデル描画ここから
	
	ground_->Draw(viewProjection_);

	//3Dモデル描画ここまで	

	//1. ビット演算を取り回しの良いUtilityクラスにする
	//2. 三項演算子をつかって、構造がわかりやすいようにする
	//piplineStatus->GetIsMesh2() ? mesh2->Draw() : ;
	//piplineStatus->GetIsSprite() ? sprite->Draw() : ;
	//piplineStatus->SetAllFlags();
	//void PipelineStatu::SetAllFlags() {
	//	bit = 0x111111111111.....;
	//}
	//void PipelineStatus::ResetAllFlags() {
		//Ethna
	//	bit = 0;
	//}

	//Sprite描画ここから


	//Sprite描画ここまで
	
	//描画ここまで
}
