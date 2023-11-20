#include "Wall.h"

Wall::Wall() {}
Wall::~Wall() {}

void Wall::Initalize(const std::vector<Model*>& models, Vector3 position)
{
	ICharacter::Initialize(models);
	worldTransform_.translation_ = position;
	BoxCollider::SetcollisionMask(~kCollitionAttributeWall);
	BoxCollider::SetcollitionAttribute(kCollitionAttributeWall);
	BoxCollider::SetParent(worldTransform_);
	BoxCollider::SetSize({ 1.0f,1.0f,1.0f });
}

void Wall::Update()
{
	ICharacter::Update();
	BoxCollider::Update(&worldTransform_);
}

void Wall::Draw(const ViewProjection& viewProjection)
{
	ICharacter::Draw(viewProjection);
}

void Wall::OnCollision(uint32_t collisionAttribute)
{
	return;
	collisionAttribute;
}

void Wall::SetScale(Vector3 scale)
{
	worldTransform_.scale_ = scale;
	BoxCollider::SetSize({ 1.0f * scale.x,1.0f,1.0f * scale.z });
}

