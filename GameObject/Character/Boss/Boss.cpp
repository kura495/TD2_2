#include "Boss.h"

Boss::Boss() {}
Boss::~Boss() {}

void Boss::Initialize(const std::vector<Model*>& models, Vector3 position)
{
	ICharacter::Initialize(models);
	worldTransform_.translation_ = position;
	worldTransform_.UpdateMatrix();
	BoxCollider::SetcollisionMask(~kCollitionAttributeEnemy);
	BoxCollider::SetcollitionAttribute(kCollitionAttributeEnemy);
	BoxCollider::SetParent(worldTransform_);
	BoxCollider::SetSize({ 1.0f,1.0f,1.0f });

	isHit_ = false;
}

void Boss::Update()
{
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

