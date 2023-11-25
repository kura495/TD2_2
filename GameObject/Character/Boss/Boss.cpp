#include "Boss.h"

Boss::Boss() {}
Boss::~Boss() {}

void Boss::Initialize(const std::vector<Model*>& models)
{
	ICharacter::Initialize(models);
	
	worldTransform_.Initialize();

	worldTransform_.translation_.z = 50.0f;

	BoxCollider::Initialize();
	BoxCollider::SetcollisionMask(~kCollitionAttributeEnemy);
	BoxCollider::SetcollitionAttribute(kCollitionAttributeEnemy);
	BoxCollider::SetParent(worldTransform_);
	BoxCollider::SetSize({ 1.0f,1.0f,1.0f });

	isHit_ = false;
}

void Boss::Update()
{
	if (behaviorRequest_) {
		//ふるまいの変更
		behavior_ = behaviorRequest_.value();
		//各ふるまいごとに初期化
		switch (behavior_)
		{
		case BossBehavior::kRoot:
		default:
			BehaviorRootInit();
			break;
		case BossBehavior::kAttack:
			BehaviorAttackInitialize();
		}
		behaviorRequest_ = std::nullopt;
	}
	switch (behavior_)
	{
	case BossBehavior::kRoot:
	default:
		BehaviorRootUpdate();
		break;
	case BossBehavior::kAttack:
		BehaviorAttackUpdate();

	}

	ICharacter::Update();
	BoxCollider::Update(&worldTransform_);
}

void Boss::Draw(const ViewProjection& viewProjection)
{
	ICharacter::Draw(viewProjection);
}

void Boss::OnCollision(Collider* collider)
{
	if (collider->GetcollitionAttribute() == kCollitionAttributePlayer)
	{
		isHit_ = true;
	}
}

void Boss::SetScale(Vector3 scale)
{
	worldTransform_.scale_ = scale;
	BoxCollider::SetSize({ 1.0f * scale.x,1.0f * scale.y,1.0f * scale.z });
}

void Boss::SetPosition(Vector3 position)
{
	worldTransform_.translation_ = position;
}

