#pragma once
#include "Base/Model.h"
#include "Base/WorldTransform.h"
#include "Base/ViewProjection.h"

#include "GameObject/Character/ICharacter/ICharacter.h"
#include "Base/Utility/BoxCollider.h"
#include "Base/Utility/CollisionConfig.h"

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

	void SetIsHit(bool isHit) { isHit_ = isHit; }

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

	float speed = 0.5f;

	bool isHit_ = false;
};

