#include "GameOverState.h"
#include"ImGuiManager.h"

void GameOverState::Initialize()
{

}

void GameOverState::Update()
{
	time++;
	if (time >= 60) {
		StateNo = 1;
	}


	ImGui::Begin("Over");

	ImGui::End();

}

void GameOverState::Draw()
{

}
