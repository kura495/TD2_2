#include"Scenes/State/GameClearState.h"

void GameClearState::Initialize()
{
	input = Input::GetInstance();
}

void GameClearState::Update()
{
	//time++;
	//if (time >= 60) {
	//	StateNo = 0;
	//}

	input->GetJoystickState(0, joyState);

	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{
		StateNo = 0;
	}

	ImGui::Begin("Clear");
	ImGui::Text("GamePlay :  A Buttun");
	ImGui::End();
}

void GameClearState::Draw()
{

}

