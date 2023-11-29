#include"Scenes/State/GameTitleState.h"

void GameTitleState::Initialize()
{

	textureManager_ = TextureManager::GetInstance();
	texture_ = textureManager_->LoadTexture("resources/Title/title.png");
	titlesprite_ = std::make_unique<Sprite>();
	titlesprite_->Initialize(LeftTop[0], LeftBottom[0], RightTop[1], RightBottom[1]);
	sprite_World_.Initialize();
	input = Input::GetInstance();

	audio_ = Audio::GetInstance();
	soundHandle = audio_->LoadAudio("resources/sound/get.wav",true);
}

void GameTitleState::Update()
{
	input->GetJoystickState(0, joyState);

	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{
		StateNo = 1;
	}
	audio_->Play(soundHandle,1.0f);

	ImGui::Begin("Title");
	ImGui::Text("GamePlay :  A Buttun");
	ImGui::End();

	/*time++;
	if (time >= 60) {
		StateNo = 1;
	}*/
}

void GameTitleState::Draw()
{
	titlesprite_->Draw(sprite_World_, texture_);
}
