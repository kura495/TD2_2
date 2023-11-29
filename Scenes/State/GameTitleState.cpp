#include"Scenes/State/GameTitleState.h"

void GameTitleState::Initialize()
{
	textureManager_ = TextureManager::GetInstance();
	texture_ = textureManager_->LoadTexture("resources/Title/title.png");
	titlesprite_ = std::make_unique<Sprite>();
	titlesprite_->Initialize(LeftTop[0], LeftBottom[0], RightTop[1], RightBottom[1]);
	sprite_World_.Initialize();
}

void GameTitleState::Update()
{
	time++;
	if (time >= 60) {
		StateNo = 2;
	}
}

void GameTitleState::Draw()
{
	titlesprite_->Draw(sprite_World_, texture_);
}
