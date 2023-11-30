#pragma once
#include"IgameState.h"
#include "Input.h"
#include "Base/Math/Math_Structs.h"
#include "Base/TextureManager.h"
#include "Base/Audio/Audio.h"
#include "Base/Sprite.h"

class GameTitleState :public GameState
{
public:
	void Initialize();
	void Update();
	void Draw();

private:
	int time;
	Input* input = nullptr;
	Audio* audio_ = nullptr;

	TextureManager* textureManager_ = nullptr;
	uint32_t texture_;
	std::unique_ptr<Sprite> titlesprite_;
	WorldTransform sprite_World_;

	std::unique_ptr<Sprite> markSprite_;
	std::unique_ptr<Sprite> tutorialSprite_;
	uint32_t textureHandle_[2];
	WorldTransform sprite_mark_;
	WorldTransform sprite_tutorial_;

	bool isTutorial_;
	bool left_;
	bool right_;

	uint32_t coolTime_;

	Vector4 LeftTop[2] = {
        { 0.0f,0.0f,0.0f,1.0f },
        { 360.0f,0.0f,0.0f,1.0f }
	};
	Vector4 LeftBottom[2] = {
		{ 0.0f,720.0f,0.0f,1.0f },
		{ 360.0f,360.0f,0.0f,1.0f }
	};
	Vector4 RightTop[2] = {
		{ 360.0f,0.0f,0.0f,1.0f },
		{ 1280.0f,0.0f,0.0f,1.0f }
	};
	Vector4 RightBottom[2] = {
		{ 360.0f,180.0f,0.0f,1.0f },
		{ 1280.0f,720.0f,0.0f,1.0f }
	};

	XINPUT_STATE joyState;
	XINPUT_STATE joyStatePre;

	uint32_t BGMHundle;
};
