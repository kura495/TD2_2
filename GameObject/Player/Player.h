﻿#pragma once

#include <optional>
#include "GameObject/BaseCharacter/BaseCharacter.h"
#include "GameObject/Weapon/Weapon.h"
#include "Base/Math/Calc.h"

enum class Behavior {
	kRoot,//通常
	kAttack,//攻撃中
	kDash,//ダッシュ中
};
//ダッシュ用ワーク
struct WorkDash {
	//ダッシュ用の媒介変数
	uint32_t dashParameter_ = 0;
	//ダッシュ用スピード
	float dashSpeed_ = 5.0f;
};

class Player : public BaseCharacter , public BoxCollider
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

	void OnCollision(const uint32_t collisionAttribute)override;
	
	void SetParent(const WorldTransform* parent);
	void DeleteParent() {
		if (!worldTransform_.parent_) {
			return;
		}
		worldTransform_.translation_ = Add(worldTransform_.GetTranslateFromMatWorld(),{0.0f,0.0f,0.0f});
		worldTransform_.parent_ = nullptr; }

	Weapon* GetWeapon() { return weapon_.get(); }

private:


	void WorldTransformInitalize();
	
	void Move();
	float targetAngle;
	
	void ApplyGlobalVariables();
	//通常
	void BehaviorRootInit();
	void BehaviorRootUpdate();
	//攻撃
	void BehaviorAttackInit();
	void BehaviorAttackUpdate();
	int attackAnimationFrame;
	//ダッシュ
	void BehaviorDashInit();
	void BehaviorDashUpdate();
	WorkDash workDash_;
	//ダッシュの時間
	const uint32_t behaviorDashTime = 20;

	//ふるまい
	Behavior behavior_ = Behavior::kRoot;
	//次のふるまいリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;
	//キー入力とパッド
	Input* input = nullptr;
	XINPUT_STATE joyState;
	//Weapon
	std::unique_ptr<Weapon>weapon_;
	WorldTransform worldTransform_Weapon_;
	//各パーツのローカル座標
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;

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
	
};

