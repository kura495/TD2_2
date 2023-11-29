#include "GameOverState.h"
#include"ImGuiManager.h"

void GameOverState::Initialize()
{
	input = Input::GetInstance();
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize(Vector4{0.0f, 0.0f, 0.0f, 1.0f}, Vector4{0.0f, 720.0f, 0.0f, 1.0f}, Vector4{1280.0f, 0.0f, 0.0f, 1.0f}, Vector4{1280.0f, 720.0f, 0.0f, 1.0f});

	worldTransform_Sprite_.Initialize();
	worldTransform_Sprite_.UpdateMatrix();
	textureHandle_ = TextureManager::GetInstance()->LoadTexture("resources/GameOver/gameOver.png");
}

void GameOverState::Update()
{
	joyStatePre = joyState;
	/*time++;
	if (time >= 60) {
		StateNo = 0;
	}*/

	input->GetJoystickState(0, joyState);

	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{
		if (!(joyStatePre.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
			StateNo = 0;
		}

		
	}

	ImGui::Begin("Over");
	ImGui::Text("GamePlay :  A Buttun");
	ImGui::End();
}

void GameOverState::Draw()
{
	sprite_->Draw(worldTransform_Sprite_, textureHandle_);
}
