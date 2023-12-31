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
	BoxCollider::SetSize({ 2.0f,2.0f,2.0f });
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

void Wall::OnCollision(Collider* collider)
{
	return;
	collider;
}

void Wall::SetScale(Vector3 scale)
{
	worldTransform_.scale_ = scale;
	BoxCollider::SetSize({ 2.0f * scale.x,2.0f * scale.y,2.0f * scale.z });
}

