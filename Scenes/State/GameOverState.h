#pragma once
#include"IgameState.h"

class GameOverState :public GameState
{
public:
	void Initialize();
	void Update();
	void Draw();

private:
	int time;
};


