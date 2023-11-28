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

	if (worldTransform_.translation_.z <= -180.0f || worldTransform_.translation_.z >= 180.0f ||
		worldTransform_.translation_.x <= -180.0f || worldTransform_.translation_.x >= 180.0f)
	{
		isDead_ = true;
	}

	worldTransform_.quaternion = Slerp(worldTransform_.quaternion, moveQuaternion_, 0.3f);

	worldTransform_.quaternion = Normalize(worldTransform_.quaternion);

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
	changeBehaviorTimer_ = 120;
}

void Boss::BehaviorRootUpdate()
{
	changeBehaviorTimer_--;

	Vector3 currentPlayerPosition = player_->GetCurrentPosition();

	Vector3 velocity = Subtract(currentPlayerPosition, currentPosition_);

	velocity = Normalize(velocity);
	Vector3 cross = Normalize(Cross({ 0.0f,0.0f,1.0f }, velocity));
	float dot = Dot({ 0.0f,0.0f,1.0f },velocity);

	velocity.x *= 0.3f;
	velocity.y *= 0.3f;
	velocity.z *= 0.3f;

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity);

	moveQuaternion_ = MakeRotateAxisAngleQuaternion(cross, std::acos(dot));

	if (changeBehaviorTimer_ < 0)
	{
		behaviorRequest_ = BossBehavior::kAttack;
	}
}

void Boss::BehaviorAttackInitialize()
{
	chargeTimer_ = 120;
	attackTimer_ = 120;
	isAttack_ = false;
}

void Boss::BehaviorAttackUpdate()
{
	if (isAttack_ == false)
	{
		chargeTimer_--;

		Vector3 currentPlayerPosition = player_->GetCurrentPosition();

		velocity_ = Subtract(currentPlayerPosition, currentPosition_);

		velocity_ = Normalize(velocity_);
		Vector3 cross = Normalize(Cross({ 0.0f,0.0f,1.0f }, velocity_));
		float dot = Dot({ 0.0f,0.0f,1.0f }, velocity_);

		moveQuaternion_ = MakeRotateAxisAngleQuaternion(cross, std::acos(dot));

	}
	
	if (chargeTimer_ < 0)
	{
		isAttack_ = true;
	}

	if (isAttack_)
	{
		attackTimer_--;
		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

		if (attackTimer_ < 0 || worldTransform_.translation_.x <= -175.0f || worldTransform_.translation_.x >= 175.0f||
			worldTransform_.translation_.z <= -175.0f || worldTransform_.translation_.z >= 175.0f)
		{
			behaviorRequest_ = BossBehavior::kRoot;
			isAttack_ = false;
		}
	}
}