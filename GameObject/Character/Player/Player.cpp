#include "Player.h"

void Player::Initialize(const std::vector<Model*>& models)
{
	std::vector<Model*> PlayerModel = { models[kModelIndexBody],models[kModelIndexHead],models[kModelIndexL_arm],models[kModelIndexR_arm]
	};
	ICharacter::Initialize(PlayerModel);
	
	BoxCollider::Initialize();
	input = Input::GetInstance();


	WorldTransformInitalize();

	const char* groupName = "Player";
	BoxCollider::SetcollisionMask(~kCollitionAttributePlayer);
	BoxCollider::SetcollitionAttribute(kCollitionAttributePlayer);
	BoxCollider::SetParent(worldTransform_);
	BoxCollider::SetSize({ 3.0f,3.0f,1.0f });
	GlobalVariables::GetInstance()->CreateGroup(groupName);
	GlobalVariables::GetInstance()->AddItem(groupName, "DashSpeed", workDash_.dashSpeed_);
}

void Player::Update()
{
	//jsonファイルの内容を適応
	ApplyGlobalVariables();
	//パッドの状態をゲット
	input->GetJoystickState(0, joyState);

	if (behaviorRequest_) {
		//ふるまいの変更
		behavior_ = behaviorRequest_.value();
		//各ふるまいごとに初期化
		switch (behavior_)
		{
		case Behavior::kRoot:
		default:
			BehaviorRootInit();
			break;
		case Behavior::kAttack:
			BehaviorAttackInit();
			break;
		case Behavior::kDash:
			BehaviorDashInit();
			break;
		}
		behaviorRequest_ = std::nullopt;
	}
	switch (behavior_)
	{
	case Behavior::kRoot:
	default:
		BehaviorRootUpdate();
		break;
	case Behavior::kAttack:
		BehaviorAttackUpdate();
		break;
	case Behavior::kDash:
		BehaviorDashUpdate();
		break;
	}

	PullDown();

	if (worldTransform_.translation_.y <= -10.0f) {
		//地面から落ちたらリスタートする
		worldTransform_.translation_ = { 0.0f,0.0f,0.0f };
		speed = 0.5f;
		worldTransform_.UpdateMatrix();
	}

	worldTransform_.quaternion = Slerp(worldTransform_.quaternion, moveQuaternion_, 0.3f);

	worldTransform_.quaternion = Normalize(worldTransform_.quaternion);


	ICharacter::Update();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
	BoxCollider::Update(&worldTransform_);


}

void Player::Draw(const ViewProjection& viewProjection)
{
	models_[kModelIndexBody]->Draw(worldTransformBody_, viewProjection);
	models_[kModelIndexHead]->Draw(worldTransformHead_, viewProjection);
	models_[kModelIndexL_arm]->Draw(worldTransformL_arm_, viewProjection);
	models_[kModelIndexR_arm]->Draw(worldTransformR_arm_, viewProjection);
}

void Player::OnCollision(const uint32_t collisionAttribute)
{
	//当たり判定
	if (collisionAttribute == kCollitionAttributeEnemy) {
		//敵に当たったらリスタートする
		worldTransform_.translation_ = { 0.0f,0.0f,0.0f };
		speed = 0.5f;
		worldTransform_.UpdateMatrix();
		behaviorRequest_ = Behavior::kRoot;
	}
	else if (collisionAttribute == kCollitionAttributeGround) {
		IsOnGraund = true;
		ImGui::Begin("Ground");
		ImGui::Text("Hit");
		ImGui::End();
	}
	else if (collisionAttribute == kCollitionAttributeWall) {
		ImGui::Begin("Wall");
		ImGui::Text("Hit");
		ImGui::End();
	}
	else if (collisionAttribute == kCollitionAttributeBuffItem) {
		speed += 0.1f;
		ImGui::Begin("BuffItem");
		ImGui::Text("Hit");
		ImGui::Text("%f", speed);
		ImGui::End();
	}
	else if (collisionAttribute == kCollitionAttributeGoal) {
		//ゴールしたらリスタートする
		worldTransform_.translation_ = { 0.0f,0.0f,0.0f };
		worldTransform_.UpdateMatrix();
		behaviorRequest_ = Behavior::kRoot;
	}
	else {
		return;
	}

}

void Player::SetParent(const WorldTransform* parent)
{
	// 親子関係を結ぶ
	if (!worldTransform_.parent_) {
		worldTransform_.parent_ = parent;
		Vector3 Pos = Subtract(worldTransform_.GetTranslateFromMatWorld(), parent->GetTranslateFromMatWorld());
		worldTransform_.translation_ = Pos;
		worldTransform_.UpdateMatrix();
	}
}

void Player::WorldTransformInitalize()
{
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
	//腕の位置調整
	worldTransformL_arm_.translation_.y = 1.4f;
	worldTransformR_arm_.translation_.y = 1.4f;
	//武器の位置調整

	worldTransformHead_.parent_ = &worldTransformBody_;
	worldTransformL_arm_.parent_ = &worldTransformBody_;
	worldTransformR_arm_.parent_ = &worldTransformBody_;
	worldTransformBody_.parent_ = &worldTransform_;
}

void Player::Move()
{
	//移動量
	if (joyState.Gamepad.sThumbLX == 0 && joyState.Gamepad.sThumbLX == 0 && joyState.Gamepad.sThumbLY == 0 && joyState.Gamepad.sThumbLY == 0) {
		return;
	}
	Vector3 move{
		(float)joyState.Gamepad.sThumbLX / SHRT_MAX, 0.0f,
		(float)joyState.Gamepad.sThumbLY / SHRT_MAX };
	//正規化をして斜めの移動量を正しくする
	move.x = Normalize(move).x * speed;
	move.y = Normalize(move).y * speed;
	move.z = Normalize(move).z * speed;
	//カメラの正面方向に移動するようにする
	//回転行列を作る
	Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_->rotation_);
	//移動ベクトルをカメラの角度だけ回転
	move = TransformNormal(move, rotateMatrix);
	//移動
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	//プレイヤーの向きを移動方向に合わせる
	//playerのY軸周り角度(θy)
	move = Normalize(move);
	Vector3 cross = Normalize(Cross({ 0.0f,0.0f,1.0f }, move));
	float dot = Dot({ 0.0f,0.0f,1.0f }, move);
	moveQuaternion_ = MakeRotateAxisAngleQuaternion(cross, std::acos(dot));
	//FIXME: クォータニオンで回転は出来たものの、平べったくなってしまう

}

void Player::ApplyGlobalVariables()
{
	const char* groupName = "Player";
	workDash_.dashSpeed_ = GlobalVariables::GetInstance()->GetfloatValue(groupName, "DashSpeed");
}

void Player::BehaviorRootInit()
{
	InitializeFloatingGimmick();
	worldTransformL_arm_.rotation_.x = 0.0f;
	worldTransformR_arm_.rotation_.x = 0.0f;
}

void Player::BehaviorRootUpdate()
{
	UpdateFloatingGimmick();
	Move();
	//RTで攻撃
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		behaviorRequest_ = Behavior::kAttack;
	}
	//Aでダッシュ
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		behaviorRequest_ = Behavior::kDash;
	}

}

void Player::BehaviorAttackInit()
{
	worldTransformL_arm_.rotation_.x = (float)std::numbers::pi;
	worldTransformR_arm_.rotation_.x = (float)std::numbers::pi;
	attackAnimationFrame = 0;
}

void Player::BehaviorAttackUpdate()
{
	
}

void Player::BehaviorDashInit()
{
	workDash_.dashParameter_ = 0;
	//プレイヤーの旋回の補間を切って一瞬で目標角度をに付くようにしている	
	worldTransform_.rotation_.y = targetAngle;
}

void Player::BehaviorDashUpdate()
{
	Vector3 move = { 0.0f,0.0f,1.0f };
	//正規化をして斜めの移動量を正しくする
	move.z = Normalize(move).z * workDash_.dashSpeed_;
	//プレイヤーの正面方向に移動するようにする
	//回転行列を作る
	Matrix4x4 rotateMatrix = MakeRotateMatrix(worldTransform_.rotation_);
	//移動ベクトルをカメラの角度だけ回転
	move = TransformNormal(move, rotateMatrix);
	//移動
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	if (++workDash_.dashParameter_ >= behaviorDashTime) {
		behaviorRequest_ = Behavior::kRoot;
	}
}


void Player::InitializeFloatingGimmick() {
	floatingParameter_ = 0.0f;
}

void Player::UpdateFloatingGimmick() {
	// 浮遊移動のサイクル<frame>
	const uint16_t T = (uint16_t)floatcycle_;
	// 1フレームでのパラメータ加算値
	const float step = 2.0f * (float)std::numbers::pi / T;
	// パラメータを1ステップ分加算
	floatingParameter_ += step;
	// 2πを超えたら0に戻す
	floatingParameter_ = (float)std::fmod(floatingParameter_, 2.0f * std::numbers::pi);
	// 浮遊の振幅<m>
	const float floatingAmplitude = floatingAmplitude_;
	// 浮遊を座標に反映
	worldTransformBody_.translation_.y = std::sin(floatingParameter_) * floatingAmplitude;

}

void Player::PullDown()
{
	if (IsOnGraund) {
		IsOnGraund = false;
		return;
	}
	else {
		worldTransform_.translation_.y -= DownForce;
	}
}

void Player::SetScale(Vector3 scale)
{
	worldTransform_.scale_ = scale;
	BoxCollider::SetSize({ 3.0f * scale.x,3.0f * scale.y,1.0f * scale.z });
}