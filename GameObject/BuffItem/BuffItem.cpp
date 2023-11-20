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
	BoxCollider::SetSize({ 1.0f,1.0f,1.0f });
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
	BoxCollider::SetSize({ 1.0f * scale.x,1.0f * scale.y,1.0f * scale.z });
}

void BuffItem::SetPosition(Vector3 position)
{
	worldTransform_.translation_ = position;
}


