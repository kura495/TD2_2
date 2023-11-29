#include"Scenes/State/GameClearState.h"

void GameClearState::Initialize()
{

}

void GameClearState::Update()
{
	time++;
	if (time >= 60) {
		StateNo = 0;
	}

	ImGui::Begin("Clear");
	ImGui::Text("%d", StateNo);
	ImGui::End();
}

void GameClearState::Draw()
{

}

