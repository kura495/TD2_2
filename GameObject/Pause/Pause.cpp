#include "Pause.h"

#include <TextureManager.h>


void Pause::Initialize() {
	Vector4 leftTop_ = { 0.0f, 0.0f, 0.0f, 1.0f };
	Vector4 leftBottom_ = { 0.0f, 512.0f, 0.0f, 1.0f };
	Vector4 rightTop_ = { 512.0f, 0.0f, 0.0f, 1.0f };
	Vector4 rightBottom_ = { 512.0f, 512.0f, 0.0f, 1.0f };

	spriteBase_ = new Sprite();
	spriteBase_->Initialize(leftTop_, leftBottom_, rightTop_, rightBottom_);

	spriteTutorial_ = new Sprite();
	spriteTutorial_->Initialize(leftTop_, leftBottom_, rightTop_, rightBottom_);

	leftTop_ = { 0.0f, 0.0f, 0.0f, 1.0f };
	leftBottom_ = { 0.0f, 128.0f, 0.0f, 1.0f };
	rightTop_ = { 128.0f, 0.0f, 0.0f, 1.0f };
	rightBottom_ = { 128.0f, 128.0f, 0.0f, 1.0f };
	spriteMark_ = new Sprite();
	spriteMark_->Initialize(leftTop_, leftBottom_, rightTop_, rightBottom_);

	worldTransformBase_.Initialize();
	worldTransformBase_.translation_ = Vector3{ 384.0f, 10.0f, 0.0f };
	worldTransformBase_.UpdateMatrix();

	worldTransformMark_.Initialize();
	worldTransformMark_.UpdateMatrix();

	worldTransformTutorial_.Initialize();
	worldTransformTutorial_.translation_ = Vector3{ 384.0f, 10.0f, 0.0f };
	worldTransformTutorial_.UpdateMatrix();

	textureHandle_[static_cast<UINT>(TextureType::kBase)] = TextureManager::GetInstance()->LoadTexture("resources/option.png");
	textureHandle_[static_cast<UINT>(TextureType::kMark)] = TextureManager::GetInstance()->LoadTexture("resources/mark.png");
	textureHandle_[static_cast<UINT>(TextureType::kTutorial)] = TextureManager::GetInstance()->LoadTexture("resources/Tutorial.png");

	left_ = true;
	right_ = false;
	isTutorial_ = false;
	coolTime_ = 0;

}

void Pause::Update() {
	preJoyState_ = joyState_;

	Input::GetInstance()->GetJoystickState(0, joyState_);
	if (!isTutorial_) {
		if (joyState_.Gamepad.sThumbLX / SHRT_MAX > 0.0f || joyState_.Gamepad.sThumbLX / SHRT_MAX < 0.0f) {
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
		worldTransformMark_.translation_ = {370.0f, 125.0f, 0.0f};

	}
	else if (right_) {
		worldTransformMark_.translation_ = {630.0f, 125.0f, 0.0f};
		if (joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
			if (!(preJoyState_.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
				isTutorial_ ^= true;
			}
		}
	}



	worldTransformBase_.UpdateMatrix();
	worldTransformMark_.UpdateMatrix();
}

void Pause::Draw() {

	spriteBase_->Draw(worldTransformBase_, textureHandle_[static_cast<UINT>(TextureType::kBase)]);

	spriteMark_->Draw(worldTransformMark_, textureHandle_[static_cast<UINT>(TextureType::kMark)]);

	if (isTutorial_) {
		spriteTutorial_->Draw(worldTransformTutorial_, textureHandle_[static_cast<UINT>(TextureType::kTutorial)]);
	}
}



