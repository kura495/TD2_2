#include "BuffItem.h"

BuffItem::BuffItem() {}
BuffItem::~BuffItem() {}

void BuffItem::Initalize(const std::vector<Model*>& models, Vector3 position)
{
	ICharacter::Initialize(models);
	worldTransform_.translation_ = position;
	worldTransform_.UpdateMatrix();
	BoxCollider::SetcollisionMask(~kCollitionAttributeBuffItem);
	BoxCollider::SetcollitionAttribute(kCollitionAttributeBuffItem);
	BoxCollider::SetParent(worldTransform_);
	BoxCollider::SetSize({ 10.0f,0.0f,10.0f });
}

void BuffItem::Update()
{
	ICharacter::Update();
	BoxCollider::Update(&worldTransform_);
}

void BuffItem::Draw(const ViewProjection& viewProjection)
{
	ICharacter::Draw(viewProjection);
}

void BuffItem::OnCollision(uint32_t collisionAttribute)
{
	return;
	collisionAttribute;
}

void BuffItem::SetScale(Vector3 scale)
{
	worldTransform_.scale_ = scale;
	BoxCollider::SetSize({ 10.0f * scale.x,0.0f,10.0f * scale.z });
}


