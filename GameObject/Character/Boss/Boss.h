#pragma once
#include "Base/Model.h"
#include "Base/WorldTransform.h"
#include "Base/ViewProjection.h"

#include "GameObject/Character/ICharacter/ICharacter.h"
#include "Base/Utility/BoxCollider.h"
#include "Base/Utility/CollisionConfig.h"
#include "GameObject/Character/Player/Player.h"

class Player;

enum class BossBehavior {
	kRoot,//通常
	kAttack,//攻撃中
};

class Boss : public ICharacter, public BoxCollider
{
public:
	Boss();
	~Boss();

	void Initialize(const std::vector<Model*>& models);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	void OnCollision(Collider* collider)override;

	void SetScale(Vector3 scale);

	void SetPosition(Vector3 position);

	bool GetIsHit() { return isHit_; }

	void SetIsHit(bool isHit) { isHit_ = isHit; }

	bool GetIsAttack() { return isAttack_; }

	bool GetIsDead() { return isDead_; }

	Vector3 GetCurrentPosition() { return currentPosition_; };
	Vector3 GetPreviousPosition() { return previousPosition_; };

	void SetPlayer(Player* player) { player_ = player; }

private:
	//通常
	void BehaviorRootInitialize();
	void BehaviorRootUpdate();

	//攻撃
	void BehaviorAttackInitialize();
	void BehaviorAttackUpdate();

	//ふるまい
	BossBehavior behavior_ = BossBehavior::kRoot;
	//次のふるまいリクエスト
	std::optional<BossBehavior> behaviorRequest_ = std::nullopt;

	Vector3 currentPosition_;  // 現在のフレームでの位置
	Vector3 previousPosition_; // 前のフレームでの位置

	float speed = 0.5f;

	bool isHit_ = false;

	bool isAttack_ = false;

	bool isDead_ = false;

	Player* player_ = nullptr;

	int underAttackTimer = 60;
};

