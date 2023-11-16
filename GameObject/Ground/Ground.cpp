#include "Ground.h"

void Ground::Initialize(Model* model, const Vector3& position)
{
	assert(model);
	model_ = model;
	worldTransform_.translation_ = position;

	worldTransform_.Initialize();
	BoxCollider::SetcollisionMask(~kCollitionAttributeFloor);
	BoxCollider::SetcollitionAttribute(kCollitionAttributeFloor);
	BoxCollider::SetParent(worldTransform_);
	BoxCollider::SetSize({ 10.0f,0.0f,10.0f });
}

void Ground::Update()
{
	worldTransform_.UpdateMatrix();
	BoxCollider::Update(&worldTransform_);
}

void Ground::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}

void Ground::OnCollision(uint32_t collisionAttribute)
{
	return;
	collisionAttribute;
}