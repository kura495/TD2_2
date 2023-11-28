#include "FollowCamera.h"
#include <Calc.h>

void FollowCamera::Initalize() {
	viewProjection_.Initialize();

	const char* groupName = "Camera";
	GlobalVariables::GetInstance()->CreateGroup(groupName);
	GlobalVariables::GetInstance()->AddItem(groupName, "interpolationPatameter", workInter.interParameter_);
}

void FollowCamera::Update() {

	ApplyGlobalVariables();
	if (target_) {
		Vector3 pos = target_->translation_;
		//もしペアレントを結んでいるなら
		if (target_->parent_) {
			pos = Add(target_->translation_, target_->parent_->translation_);
		}
		//追従座標の補間
		workInter.interTarget_ = VectorLerp(workInter.interTarget_, pos, workInter.interParameter_);

		Vector3 offset = OffsetCalc();
		//オフセット分と追従座標の補間分ずらす
		viewProjection_.translation_ = workInter.interTarget_ + offset;
	}
	//スティックでのカメラ回転
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
			float angle = (float)joyState.Gamepad.sThumbLX / 720.0f * 3.14159265359f / 180.0f;
			if (anglePre_ == 0.0f) {
				anglePre_ = viewProjection_.rotation_.y;
			}

			if (isStickRightPre_) {
				if (angle < 0.0f) {
					angle = 0.0f;
				}
			}
			else if (isStickLeftPre_) {
				if (angle > 0.0f) {
					angle = 0.0f;
				}
			}

			float destinationAngleY = anglePre_ + angle;
			viewProjection_.rotation_.y = LerpShortAngle(viewProjection_.rotation_.y, destinationAngleY, 0.2f);

			
		}
		else {
			const float kRadian = 0.02f;
			viewProjection_.rotation_.y += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * kRadian;
			anglePre_ = 0.0f;
		}
	}

	viewProjection_.UpdateViewMatrix();
	viewProjection_.TransferMatrix();
	isStickRightPre_ = false;
	isStickLeftPre_ = false;
}

void FollowCamera::SetTarget(const WorldTransform* target)
{
	target_ = target;
	Reset();
}

void FollowCamera::ApplyGlobalVariables()
{
	const char* groupName = "Camera";
	workInter.interParameter_ = GlobalVariables::GetInstance()->GetfloatValue(groupName, "interpolationPatameter");
}

void FollowCamera::Reset()
{
	//追従対象がいれば
	if (target_) {
		//追従座標・角度の初期化
		workInter.interTarget_ = target_->translation_;
		viewProjection_.rotation_.y = target_->rotation_.y;
	}
	workInter.targetAngleY_ = viewProjection_.rotation_.y;

	//追従大賞からのオフセット
	Vector3 offset = OffsetCalc();
	viewProjection_.translation_ = workInter.interTarget_ + offset;
}

Vector3 FollowCamera::OffsetCalc()
{
	Vector3 offset = { 0.0f, 30.0f, -105.0f };
	//回転行列の合成
	Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_.rotation_);

	// オフセットをカメラの回転に合わせて回転
	offset = TransformNormal(offset, rotateMatrix);

	return offset;
}