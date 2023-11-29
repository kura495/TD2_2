#pragma once

#include <Sprite.h>
#include <WorldTransform.h>
#include <ViewProjection.h>
#include <memory>
#include <Input.h>

class Pause
{
public:
	enum class TextureType {
		kBase,
		kMark,
		kTutorial,
	};

	struct SizeToPos {
		Vector3 size_;
		Vector3 position_;
	};

public:
	

	void Initialize();
	void Update();
	void Draw();

	bool GetLeft() { return left_; };
	bool Getright() { return right_; };
	void SetIsTutorial(bool isTutorial) {isTutorial_ = isTutorial;}

private:
	XINPUT_STATE joyState_;
	XINPUT_STATE preJoyState_;

	Sprite* spriteBase_;
	Sprite* spriteMark_;
	Sprite* spriteTutorial_;

	uint32_t textureHandle_[3];

	WorldTransform worldTransformBase_;

	WorldTransform worldTransformMark_;

	WorldTransform worldTransformTutorial_;

	bool left_;
	bool right_;

	bool isTutorial_;

	uint32_t coolTime_;

	/*SizeToPos base_;
	SizeToPos mark_;*/


};

