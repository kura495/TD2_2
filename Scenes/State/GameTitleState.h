#pragma once
#include"IgameState.h"
#include "Base/Math/Math_Structs.h"
#include "Base/TextureManager.h"
#include "Base/Sprite.h"

class GameTitleState :public GameState
{
public:
	void Initialize();
	void Update();
	void Draw();

private:
	int time;
	TextureManager* textureManager_ = nullptr;
	uint32_t texture_;
	std::unique_ptr<Sprite> titlesprite_;
	WorldTransform sprite_World_;

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
};
