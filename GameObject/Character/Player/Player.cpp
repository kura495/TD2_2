#include "Player.h"
#include "GameObject/Character/Boss/Boss.h"

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
	//GlobalVariables::GetInstance()->AddItem(groupName, "DashSpeed", workDash_.dashSpeed_);
}

void Player::Update()
{
	previousPosition_ = currentPosition_;
	// プレイヤーキャラクターの位置を更新
	currentPosition_ = worldTransform_.translation_;

	//jsonファイルの内容を適応
	ApplyGlobalVariables();
	//パッドの状態をゲット
	input->GetJoystickState(0, joyState);

	float normalizedX = static_cast<float>(joyState.Gamepad.sThumbLX) / SHRT_MAX;
	if (normalizedX > threshold_) {
		isStickRight_ = true;
	}
	else {
		isStickRight_ = false;
	}

	if (normalizedX < -threshold_)
	{
		isStickLeft_ = true;

	}
	else {
		isStickLeft_ = false;
	}

	if (!IsOnGraund && behavior_ != Behavior::kJump) {
		worldTransform_.translation_ = Add(worldTransform_.translation_, workJump_.velocity_);

		const float kGravityAcceleration_ = 0.05f;

		Vector3 accelerationVector_ = { 0.0f,-kGravityAcceleration_,0.0f };

		workJump_.velocity_ = Add(workJump_.velocity_, accelerationVector_);
	}


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
		case Behavior::kDash:
			BehaviorDashInit();
			break;
		case Behavior::kJump:
			BehaviorJumpInitialize();
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
	case Behavior::kDash:
		BehaviorDashUpdate();
		break;
	case Behavior::kJump:
		BehaviorJumpUpdate();
		break;
	}

	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B && IsOnGraund)
	{
		behaviorRequest_ = Behavior::kJump;
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

	//if (isEnemyHit_)
	//{
	//	Vector3 currentBossPosition = boss_->GetCurrentPosition();
	//	Vector3 previousBossPosition = boss_->GetPreviousPosition();

	//	Vector3 velocity = Subtract(currentBossPosition, previousBossPosition);

	//	worldTransform_.translation_ = Subtract(worldTransform_.translation_, velocity);

	///*	isEnemyHit_ = false;*/
	//}

	ICharacter::Update();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
	BoxCollider::Update(&worldTransform_);

	joyStatePre = joyState;

	isHit_ = false;
}

void Player::Draw(const ViewProjection& viewProjection)
{
	models_[kModelIndexBody]->Draw(worldTransformBody_, viewProjection);
	models_[kModelIndexHead]->Draw(worldTransformHead_, viewProjection);
	models_[kModelIndexL_arm]->Draw(worldTransformL_arm_, viewProjection);
	models_[kModelIndexR_arm]->Draw(worldTransformR_arm_, viewProjection);
}

void Player::OnCollision(Collider* collider)
{

	if (collider->GetcollitionAttribute() == kCollitionAttributeEnemy && workDash_.isDash == true) {
		//敵に当たったらリスタートする
		//isDead_ = true;
	/*	worldTransform_.translation_ = { 0.0f,0.0f,0.0f };
		speed = 0.5f;
		worldTransform_.UpdateMatrix();
		behaviorRequest_ = Behavior::kRoot;*/
		isEnemyHit_ = true;

	}
	else if (collider->GetcollitionAttribute() == kCollitionAttributeGround) {
		IsOnGraund = true;
		isHit_ = true;
		workJump_.velocity_.y = 0.0f;
		ImGui::Begin("Ground");
		ImGui::Text("Hit");
		ImGui::End();
	
	}
	else if (collider->GetcollitionAttribute() == kCollitionAttributeWall) {
		worldTransform_.translation_ = previousPosition_;
		
		if (!IsOnGraund) {
			workJump_.velocity_.x *= -10.0f;
			workJump_.velocity_.z *= -10.0f;
		}
		

		
		
		isHit_ = true;
		//workJump_.velocity_.y = 0.0f;
		ImGui::Begin("Wall");
		ImGui::Text("Hit");
		ImGui::End();
	}
	else if (collider->GetcollitionAttribute() == kCollitionAttributeBuffItem) {
     /*   speed += 0.1f;*/
		ImGui::Begin("BuffItem");
		ImGui::Text("Hit");
		ImGui::Text("%f", speed);
		ImGui::End();
	}
	else if (collider->GetcollitionAttribute() == kCollitionAttributeGoal) {
		isGoal_ = true;
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
		workJump_.velocity_ = { 0.0f, 0.0f, 0.0f };
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
	workJump_.velocity_ = move;
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
	//const char* groupName = "Player";
	//workDash_.dashSpeed_ = GlobalVariables::GetInstance()->GetfloatValue(groupName, "DashSpeed");
}

void Player::BehaviorRootInit()
{
	InitializeFloatingGimmick();
	worldTransformL_arm_.rotation_.x = 0.0f;
	worldTransformR_arm_.rotation_.x = 0.0f;
	workJump_.kSpped_ = 1.0f;
}

void Player::BehaviorRootUpdate()
{
	UpdateFloatingGimmick();
	Move();
	
	//Aでダッシュ
	if (workDash_.coolTime_++ >= dashCoolTime_) {
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
			behaviorRequest_ = Behavior::kDash;
		}
	}

}


void Player::BehaviorDashInit()
{
	workDash_.dashParameter_ = 0;
	workDash_.chargeParameter_ = 0;
	//プレイヤーの旋回の補間を切って一瞬で目標角度をに付くようにしている	
	worldTransform_.rotation_.y = targetAngle;
	workDash_.coolTime_ = 0;
	workDash_.isPowerCharge = true;
	workDash_.isDash = false;
	workDash_.dashPower_ = 0.0f;
	workDash_.kSpeed_ = 1.0f;
	workDash_.scale_ = worldTransformBody_.scale_;
	workDash_.quaternionPre_ = worldTransform_.quaternion;
}

void Player::BehaviorDashUpdate()
{
	Input::GetInstance()->GetJoystickState(0, joyState);
	if (workDash_.isPowerCharge) {
		workDash_.move_  = {(float)joyState.Gamepad.sThumbLX / SHRT_MAX, 0.0f,(float)joyState.Gamepad.sThumbLY / SHRT_MAX };

		if (workDash_.scale_.x > 0.5f) {
			workDash_.scale_ = Subtract(workDash_.scale_, Vector3{ 0.005f, 0.005f, 0.005f });
		}
		worldTransformBody_.scale_ = workDash_.scale_;

		//回転行列を作る
		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_->rotation_);
		//移動ベクトルをカメラの角度だけ回転
		Vector3 moveQ = TransformNormal(workDash_.move_, rotateMatrix);
		Vector3 rotate = Normalize(moveQ);
		Vector3 cross = Normalize(Cross({ 0.0f,0.0f,1.0f }, rotate));
		float dot = Dot({ 0.0f,0.0f,1.0f }, rotate);
		moveQuaternion_ = MakeRotateAxisAngleQuaternion(cross, std::acos(dot));

		if (workDash_.isDash) {
			Vector3 move = workDash_.movePre_;
			//rotateMatrix = MakeRotateMatrix(viewProjection_->rotation_);
			//移動ベクトルをカメラの角度だけ回転
			//move = TransformNormal(move, rotateMatrix);
			//回転行列を作る
			rotateMatrix = MakeRotateMatrix(worldTransform_.quaternion);
			//移動ベクトルをカメラの角度だけ回転
			move = TransformNormal(move, rotateMatrix);
			move.x *= workDash_.kSpeed_; 
			move.y *= workDash_.kSpeed_;
			move.z *= workDash_.kSpeed_;

			if (workDash_.kSpeed_ < 0.0f) {
				workDash_.kSpeed_ = 0.0f;
			}
			else {
				workDash_.kSpeed_ -= 0.01f;
			}
			//移動
			worldTransform_.translation_ = Add(worldTransform_.translation_, move);

			rotateMatrix = MakeRotateMatrix(viewProjection_->rotation_);
			move = TransformNormal(move, rotateMatrix);
			workJump_.velocity_ = move;
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B && IsOnGraund)
			{
				worldTransformBody_.scale_ = Vector3{ 1.0f, 1.0f, 1.0f };
				workJump_.kSpped_ = workDash_.kSpeed_;
			}
		}

		if (!(joyStatePre.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
			workDash_.isPowerCharge = false;
			workDash_.isDash = true;
			workDash_.chargeParameter_ = 0;
			workDash_.kSpeed_ = 1.0f;
			worldTransformBody_.scale_ = Vector3{ 1.0f, 1.0f, 1.0f };
			workDash_.scale_ = Vector3{ 1.0f, 1.0f, 1.0f };
		}

		if (workDash_.chargeParameter_++ > chargeTime) {
			worldTransformBody_.scale_ = Vector3{ 1.0f, 1.0f, 1.0f };
			workDash_.isDash = false;
			behaviorRequest_ = Behavior::kRoot;
			workDash_.isDash = false;
		}

	}
	else {
		workJump_.kSpped_ = workDash_.dashSpeed_;
		Vector3 move = workDash_.move_;
		workDash_.movePre_ = workDash_.move_;
		//回転行列を作る
		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_->rotation_);
		//移動ベクトルをカメラの角度だけ回転
		move = TransformNormal(workDash_.move_, rotateMatrix);
		workJump_.velocity_ = Normalize(move);
		//正規化をして斜めの移動量を正しくする
		move.x = Normalize(move).x * workDash_.dashSpeed_;
		move.y = Normalize(move).y * workDash_.dashSpeed_;
		move.z = Normalize(move).z * workDash_.dashSpeed_;

		//移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, move);

		workDash_.dashParameter_++;
		if ((joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
			workDash_.isPowerCharge = true;
			workDash_.dashParameter_ = 0;
		}
		

	}

	if (workDash_.dashParameter_ >= behaviorDashTime) {
		workDash_.isDash = false;
		behaviorRequest_ = Behavior::kRoot;
		workDash_.isDash = false;
	}

}


void Player::BehaviorJumpInitialize() {
	isHit_ = false;

	//workJump_.velocity_ = { (float)joyState.Gamepad.sThumbLX / (SHRT_MAX * 2), workJump_.kJumpFirstSpeed_, (float)joyState.Gamepad.sThumbLY / (SHRT_MAX * 2) };
	//Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_->rotation_);

	//workJump_.velocity_ = TransformNormal(workJump_.velocity_, rotateMatrix);
	workJump_.velocity_ = Normalize(workJump_.velocity_);
	workJump_.velocity_.y = workJump_.kJumpFirstSpeed_;
	workJump_.velocity_.x *= workJump_.kSpped_;
	workJump_.velocity_.z *= workJump_.kSpped_;
}

void Player::BehaviorJumpUpdate() {
	worldTransform_.translation_ = Add(worldTransform_.translation_, workJump_.velocity_);

	const float kGravityAcceleration_ = 0.05f;

	Vector3 accelerationVector_ = { 0.0f,-kGravityAcceleration_,0.0f };

	workJump_.velocity_ = Add(workJump_.velocity_, accelerationVector_);

	if (isHit_)
	{
		workJump_.velocity_.y = 0.0f;
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