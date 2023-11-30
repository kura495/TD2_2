#pragma once
#include <Sprite.h>
#include <WorldTransform.h>
#include <ViewProjection.h>
#include <memory>

class Timer
{
public:
	enum class DigitPlace {
		kOnes,
		kTens,
		kHundreds,
	};
public:
	Timer();
	~Timer();

	void Initialize(DigitPlace digit, uint32_t start, Vector3 translation);
	void Update();
	void Draw();
	void Set(uint32_t start);
	bool GetIsFin()const {
		return IsFin;
	};
private:
	bool IsFin = false;

	Vector4 leftTop_ = { 0.0f, 0.0f, 0.0f, 1.0f };
	Vector4 leftBottom_ = { 0.0f, 64.0f, 0.0f, 1.0f };
	Vector4 rightTop_ = { 64.0f, 0.0f, 0.0f, 1.0f };
	Vector4 rightBottom_ = { 64.0f, 64.0f, 0.0f, 1.0f };

	Sprite* sprite_;

	WorldTransform worldTransform_;

	uint32_t textureHandle_[10];
	uint32_t timer_ = 0;
	uint32_t second = 0;
	DigitPlace digitPlace_;
};