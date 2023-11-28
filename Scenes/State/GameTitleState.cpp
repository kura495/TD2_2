#include"Scenes/State/GameTitleState.h"

void GameTitleState::Initialize()
{

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

}
