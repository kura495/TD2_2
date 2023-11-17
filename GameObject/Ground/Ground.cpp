#include "Ground.h"

Ground::Ground() {}
Ground::~Ground() {}

void Ground::Initalize(const std::vector<Model*>& models, Vector3 position)
{
	ICharacter::Initialize(models);
	worldTransform_.translation_ = position;
	worldTransform_.UpdateMatrix();
	BoxCollider::SetcollisionMask(~kCollitionAttributeGround);
	BoxCollider::SetcollitionAttribute(kCollitionAttributeGround);
	BoxCollider::SetParent(worldTransform_);
	BoxCollider::SetSize({ 10.0f,0.0f,10.0f });
}

void Ground::Update()
{
	ICharacter::Update();
	BoxCollider::Update(&worldTransform_);
}

void Ground::Draw(const ViewProjection& viewProjection)
{
	ICharacter::Draw(viewProjection);
}

void Ground::OnCollision(uint32_t collisionAttribute)
{
	return;
	collisionAttribute;
}

void Ground::SetScale(Vector3 scale)
{
	worldTransform_.scale_ = scale;
	BoxCollider::SetSize({ 10.0f * scale.x,0.0f,10.0f * scale.z });
}
