#include "Timer.h"

#include <TextureManager.h>

Timer::Timer() {
	//sprietOnes_ = new Sprite();
	////spriteTen_ = new Sprite();
	//spriteHundreds_ = new Sprite();

	/*sprietOnes_ = std::make_unique<Sprite>();
	spriteTens_ = std::make_unique<Sprite>();
	spriteHundreds_ = std::make_unique<Sprite>();*/

	sprite_ = new Sprite();

	for (uint32_t i = 0; i < 10; i++) {
		textureHandle_[i] = 0;
	}

	leftTop_ = { 0.0f, 0.0f, 0.0f, 1.0f };
	leftBottom_ = { 0.0f, 64.0f, 0.0f, 1.0f };
	rightTop_ = { 64.0f, 0.0f, 0.0f, 1.0f };
	rightBottom_ = { 64.0f, 64.0f, 0.0f, 1.0f };

	digitPlace_ = DigitPlace::kOnes;
}

Timer::~Timer() {


}

void Timer::Initialize(DigitPlace digit, uint32_t start, Vector3 translation) {
	//textureManager_ = TextureManager::GetInstance();

	//sprietOnes_->Initialize(leftTop_, leftBottom_, rightTop_, rightBottom_);
	////spriteTen_->Initialize(leftTop_, leftBottom_, rightTop_, rightBottom_);
	//spriteHundreds_->Initialize(leftTop_, leftBottom_, rightTop_, rightBottom_);

	sprite_->Initialize(leftTop_, leftBottom_, rightTop_, rightBottom_);

	worldTransform_.Initialize();
	worldTransform_.translation_ = translation;
	worldTransform_.UpdateMatrix();


	digitPlace_ = digit;

	timer_ = start;
	second = 0;

	textureHandle_[0] = TextureManager::GetInstance()->LoadTexture("resources/number/0.png");
	textureHandle_[1] = TextureManager::GetInstance()->LoadTexture("resources/number/1.png");
	textureHandle_[2] = TextureManager::GetInstance()->LoadTexture("resources/number/2.png");
	textureHandle_[3] = TextureManager::GetInstance()->LoadTexture("resources/number/3.png");
	textureHandle_[4] = TextureManager::GetInstance()->LoadTexture("resources/number/4.png");
	textureHandle_[5] = TextureManager::GetInstance()->LoadTexture("resources/number/5.png");
	textureHandle_[6] = TextureManager::GetInstance()->LoadTexture("resources/number/6.png");
	textureHandle_[7] = TextureManager::GetInstance()->LoadTexture("resources/number/7.png");
	textureHandle_[8] = TextureManager::GetInstance()->LoadTexture("resources/number/8.png");
	textureHandle_[9] = TextureManager::GetInstance()->LoadTexture("resources/number/9.png");

}

void Timer::Update() {

	if (timer_ == 0) {
		second = 0;
		IsFin = true;
	}
	else {
		if (++second % 60 == 0) {
			timer_--;
		}

		if (timer_ < 15) {
			sprite_->SetColor(Vector4{ 1.0f, 0.0f, 0.0f, 1.0f });
		}
	}
}

void Timer::Draw() {
	switch (digitPlace_)
	{
	case Timer::DigitPlace::kOnes:
		sprite_->Draw(worldTransform_, textureHandle_[timer_ % 10]);
		break;
	case Timer::DigitPlace::kTens:
		sprite_->Draw(worldTransform_, textureHandle_[(timer_ / 10) % 10]);
		break;
	case Timer::DigitPlace::kHundreds:
		//sprite_->Draw(worldTransform_, textureHandle_[timer_ / 100]);
		break;
	}
}

void Timer::Set(uint32_t start) {
	start;
}