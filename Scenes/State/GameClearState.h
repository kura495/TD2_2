#pragma once
#include"IgameState.h"
#include "MyEngine.h"
#include "ModelData.h"
#include "Audio.h"
#include "Input.h"
#include "Sprite.h"
#include "TextureManager.h"

class GameClearState :public GameState
{
public:
	void Initialize();
	void Update();
	void Draw();

private:
	int time;
	Input* input = nullptr;

	XINPUT_STATE joyState;
	XINPUT_STATE joyStatePre;
};
