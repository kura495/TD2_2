#pragma once
#include"IgameState.h"
#include "MyEngine.h"
#include "ModelData.h"
#include "Audio.h"
#include "Input.h"
#include "Sprite.h"
#include "TextureManager.h"

class GameOverState : public GameState
{
public:
	void Initialize();
	void Update();
	void Draw();

private:
	int time;
	Input* input = nullptr;

	std::unique_ptr<Sprite> sprite_;
	WorldTransform worldTransform_Sprite_;
	uint32_t textureHandle_;

	XINPUT_STATE joyState;
	XINPUT_STATE joyStatePre;
};


