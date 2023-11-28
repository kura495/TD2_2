#include "Boss.h"
#include "GameObject/Character/Player/Player.h"

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
	previousPosition_ = currentPosition_;
	
	currentPosition_ = worldTransform_.translation_;

	if (behaviorRequest_) {
		//ふるまいの変更
		behavior_ = behaviorRequest_.value();
		//各ふるまいごとに初期化
		switch (behavior_)
		{
		case BossBehavior::kRoot:
		default:
			BehaviorRootInitialize();
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

	if (isHit_)
	{
		underAttackTimer--;
		Vector3 currentPlayerPosition = player_->GetCurrentPosition();
		Vector3 previousPlayerPosition = player_->GetPreviousPosition();

		Vector3 velocity = Subtract(currentPlayerPosition, previousPlayerPosition);

		velocity.x *= 3.0f;
		velocity.y *= 3.0f;
		velocity.z *= 3.0f;

		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity);


		if (underAttackTimer < 0)
		{
			isHit_ = false;
			underAttackTimer = 60;
		}
	}

	if (worldTransform_.translation_.z <= -150.0f || worldTransform_.translation_.z >= 150.0f ||
		worldTransform_.translation_.x <= -150.0f || worldTransform_.translation_.x >= 150.0f)
	{
		isDead_ = true;
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
	if (/*isAttack_ == true && */collider->GetcollitionAttribute() == kCollitionAttributePlayer && player_->GetIsDash() == true)
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

void Boss::BehaviorRootInitialize()
{
}

void Boss::BehaviorRootUpdate()
{
	
}

void Boss::BehaviorAttackInitialize()
{

}

void Boss::BehaviorAttackUpdate()
{
	isAttack_ = true;
	worldTransform_.translation_.z -= speed;
}
