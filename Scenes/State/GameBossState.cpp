#include "Scenes/State/GameBossState.h"

void GameBossState::Initialize()
{
	input = Input::GetInstance();
	audio = Audio::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	light_ = Light::GetInstance();

	DirectX_ = DirectXCommon::GetInstance();

	collisionManager_ = std::make_unique<CollisionManager>();

	viewProjection_.Initialize();
	worldTransform_.Initialize();

	skydomeModel_.reset(Model::CreateModelFromObj("resources/skydome", "skydome.obj"));

	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(skydomeModel_.get());
}

void GameBossState::Update()
{
	skydome_->Updata();

	time++;
	if (time >= 60) {
		StateNo = 1;
	}
}

void GameBossState::Draw()
{
	skydome_->Draw(viewProjection_);
}
