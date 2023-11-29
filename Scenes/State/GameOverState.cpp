#include "GameOverState.h"
#include"ImGuiManager.h"

void GameOverState::Initialize()
{
	input = Input::GetInstance();
}

void GameOverState::Update()
{
	/*time++;
	if (time >= 60) {
		StateNo = 0;
	}*/

	input->GetJoystickState(0, joyState);

	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{
		StateNo = 0;
	}

	ImGui::Begin("Over");
	ImGui::Text("GamePlay :  A Buttun");
	ImGui::End();
}

void GameOverState::Draw()
{

}
