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

	textureHandle_[0] = textureManager_->LoadTexture("resources/Pause/mark.png");
	textureHandle_[1] = textureManager_->LoadTexture("resources/Pause/tutorial.png");
	markSprite_ = std::make_unique<Sprite>();
	tutorialSprite_ = std::make_unique<Sprite>();


	markSprite_->Initialize(Vector4{ 0.0f, 0.0f, 0.0f, 1.0f }, Vector4{ 0.0f, 128.0f, 0.0f, 1.0f }, Vector4{ 128.0f, 0.0f, 0.0f, 1.0f }, Vector4{ 128.0f, 128.0f, 0.0f, 1.0f });
	tutorialSprite_->Initialize(Vector4{ 0.0f, 0.0f, 0.0f, 1.0f }, Vector4{ 0.0f, 512.0f, 0.0f, 1.0f }, Vector4{ 512.0f, 0.0f, 0.0f, 1.0f }, Vector4{ 512.0f, 512.0f, 0.0f, 1.0f });
	sprite_mark_.Initialize();

	sprite_tutorial_.Initialize();
	sprite_tutorial_.translation_ = Vector3{ 384.0f, 10.0f, 0.0f };
	sprite_tutorial_.UpdateMatrix();

	left_ = true;
	right_ = false;
	isTutorial_ = false;
	coolTime_ = 0;

	BGMHundle = audio_->LoadAudio("resources/sound/GameScene.wav",true);
}

void GameTitleState::Update()
{
	audio_->Play(BGMHundle,1.0f);

	joyStatePre = joyState;
	input->GetJoystickState(0, joyState);

	if (!isTutorial_) {
		if (joyState.Gamepad.sThumbLX / SHRT_MAX != 0.0f) {
			if (coolTime_ == 0) {
				left_ ^= true;
				right_ ^= true;
				coolTime_ = 10;
			}
		}
	}

	if (coolTime_) {
		coolTime_--;
	}

	if (left_) {
		sprite_mark_.translation_ = { 130.0f, 390.0f, 0.0f };
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
			if (!(joyStatePre.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
				audio_->Stop(BGMHundle, false);
				StateNo = 1;

			}
		}

	}
	else if (right_) {
		sprite_mark_.translation_ = { 660.0f, 390.0f, 0.0f };
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			if (!(joyStatePre.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
				isTutorial_ ^= true;

			}
		}
	}

	sprite_mark_.UpdateMatrix();

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

	markSprite_->Draw(sprite_mark_, textureHandle_[0]);

	if (isTutorial_) {
		tutorialSprite_->Draw(sprite_tutorial_, textureHandle_[1]);
	}
}
