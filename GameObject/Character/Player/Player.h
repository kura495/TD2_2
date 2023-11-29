#pragma once

#include <optional>
#include "GameObject/Character/ICharacter/ICharacter.h"
#include "Input.h"
#include "Base/Math/Calc.h"
#include "Base/Model.h"
#include "Base/WorldTransform.h"
#include "Base/ViewProjection.h"
#include "Base/Utility/BoxCollider.h"
#include "Base/Utility/CollisionConfig.h"

#include "GameObject/BuffItem/BuffItem.h"
#include "GameObject/Character/Boss/Boss.h"
#include <memory>
#include <Sprite.h>

class Boss;

enum class Behavior {
	kRoot,//通常
	kDash,//ダッシュ中
	kDrift, // ドリフト中
	kJump, // ジャンプ
};
//ダッシュ用ワーク
struct WorkDash {
	//ダッシュ用の媒介変数
	uint32_t dashParameter_ = 0;
	uint32_t chargeParameter_ = 0;
	uint32_t coolTime_ = 0;
	//ダッシュ用スピード
	float dashSpeed_ = 2.0f;
	float dashPower_ = 0.0f;
	float kSpeed_ = 1.0f;
	Vector3 move_;
	Vector3 movePre_;
	Vector3 scale_;
	Quaternion quaternionPre_;
	bool isPowerCharge;
	bool isDash;
	bool isDrift;
};
const uint32_t dashCoolTime_ = 60;
const uint32_t chargeTime = 300;
const float dashPowerMax_ = 5.0f;

struct WorkDrift {
	uint32_t driftParameter_;
	uint32_t driftChargeParameter_;
	float kSpeed_;
	Vector3 movePre_;
	Vector3 rotationAmount_;
	bool isStickRightPre_;
	bool isStickLeftPre_;
	bool isDrifting_;
};

const uint32_t behaviorDriftTime_ = 60;
const uint32_t behaviorDriftChargeTime_ = 3000;

struct WorkJump {
	Vector3 velocity_ = {0.0f, 0.0f, 0.0f};
	float kJumpFirstSpeed_ = 1.0f;
	float kGravityAcceleration_ = 0.05f;
	float kSpped_ = 1.0f;
	bool Flag_ = false;
};

class Player : public ICharacter, public BoxCollider
{
public:
	~Player() {};

	void Initialize(const std::vector<Model*>& models) override;
	void Update() override;
	void Draw(const ViewProjection& viewProjection) override;

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}
	const WorldTransform& GetWorldTransform() {
		return worldTransform_;
	}

	void OnCollision(Collider* collider)override;

	void SetParent(const WorldTransform* parent);
	void DeleteParent() {
		if (!worldTransform_.parent_) {
			return;
		}
		worldTransform_.translation_ = Add(worldTransform_.GetTranslateFromMatWorld(), { 0.0f,0.0f,0.0f });
		worldTransform_.parent_ = nullptr;
	}

	void SetScale(Vector3 scale);

	bool GetIsDead() { return isDead_; }

	bool GetIsGoal() { return isGoal_; }

	void SetIsDead(bool isDead) { isDead_ = isDead; }

	bool GetIsStickRight() { return workDrift_.isStickRightPre_; }
	bool GetIsStickLeft() { return workDrift_.isStickLeftPre_; }

	bool GetIsDash() { return  workDash_.isDash; };

	Behavior GetBehavior() { return  behavior_; };

	Vector3 GetCurrentPosition() { return currentPosition_; };
	Vector3 GetPreviousPosition() { return previousPosition_; };

	Vector3 SetCurrentPosition(Vector3 position) { currentPosition_ = position; };

	void SetBoss(Boss* boss) { boss_ = boss; }

	uint32_t GetItemCount() { return itemCount_; }

private:
	void WorldTransformInitalize();

	void Move();
	float targetAngle;

	void ApplyGlobalVariables();
	//通常
	void BehaviorRootInit();
	void BehaviorRootUpdate();
	//ダッシュ
	void BehaviorDashInit();
	void BehaviorDashUpdate();
	
	// ジャンプ
	void BehaviorJumpInitialize();
	void BehaviorJumpUpdate();

	WorkDash workDash_;
	WorkDrift workDrift_;
	WorkJump workJump_;
	//ダッシュの時間
	const uint32_t behaviorDashTime = 60;

	//ふるまい
	Behavior behavior_ = Behavior::kRoot;
	//次のふるまいリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;
	//キー入力とパッド
	Input* input = nullptr;
	XINPUT_STATE joyState;
	XINPUT_STATE joyStatePre;
	
	//各パーツのローカル座標
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	WorldTransform worldTransformLine_;
	//カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	GlobalVariables* globalVariables = nullptr;
	//プレイヤーの移動
	float speed = 0.5f;


	//浮遊ギミック
	void InitializeFloatingGimmick();
	void UpdateFloatingGimmick();
	//浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;
	int floatcycle_ = 120;
	float floatingAmplitude_ = 0.2f;

	//プレイヤーを下に引っ張る
	void PullDown();
	bool IsOnGraund = true;
	float DownForce = 0.98f;

	Quaternion moveQuaternion_;

	bool isDead_ = false;

	bool isHit_ = false;

	bool isGoal_ = false;

	bool isEnemyHit_ = false;
	
	//相殺している
	bool isOffset_ = false;

	bool isSpeedUp_ = false;

	Vector3 currentPosition_;  // 現在のフレームでの位置
	Vector3 previousPosition_; // 前のフレームでの位置

	// スティックが倒れている方
	bool isStickRight_ = false;
	bool isStickLeft_ = false;
	float threshold_ = 0.5f;

	const float M_PI = 3.14159265359f;

	Boss* boss_ = nullptr;

	int underAttackTimer = 60;

	float hitSpeed_ = 3.0f;

	uint32_t itemCount_ = 0;
};
