#include "MoveGround.h"

MoveGround::MoveGround() {}
MoveGround::~MoveGround() {}

void MoveGround::Initalize(const std::vector<Model*>& models, Vector3 position)
{
	ICharacter::Initialize(models);
	worldTransform_.translation_ = position;
	worldTransform_.UpdateMatrix();
	BoxCollider::SetcollisionMask(~kCollitionAttributeMoveGround);
	BoxCollider::SetcollitionAttribute(kCollitionAttributeMoveGround);
	BoxCollider::SetParent(worldTransform_);
	BoxCollider::SetSize({ 19.5f,0.0f,20.0f });
}

void MoveGround::Update()
{
	worldTransform_.translation_.y += speed_;

	if (worldTransform_.translation_.y >= 40.0f)
	{
		speed_ *= -1;
	}

	if (worldTransform_.translation_.y <= 0.0f)
	{
		speed_ *= -1;
	}

	ICharacter::Update();
	BoxCollider::Update(&worldTransform_);
}

void MoveGround::Draw(const ViewProjection& viewProjection)
{
	ICharacter::Draw(viewProjection);
}

void MoveGround::OnCollision(Collider* collider)
{
	return;
	collider;
}

void MoveGround::SetScale(Vector3 scale)
{
	worldTransform_.scale_ = scale;
	BoxCollider::SetSize({ 19.5f * scale.x,0.0f,20.0f * scale.z });
}

