#include "BuffItem.h"

BuffItem::BuffItem() {}
BuffItem::~BuffItem() {}

void BuffItem::Initalize(const std::vector<Model*>& models, Vector3 position)
{
	audio_ = Audio::GetInstance();

	ICharacter::Initialize(models);
	worldTransform_.translation_ = position;
	worldTransform_.UpdateMatrix();
	BoxCollider::SetcollisionMask(~kCollitionAttributeBuffItem);
	BoxCollider::SetcollitionAttribute(kCollitionAttributeBuffItem);
	BoxCollider::SetParent(worldTransform_);
	BoxCollider::SetSize({ 1.0f,1.0f,1.0f });

	isHit_ = false;
	isActive_ = true;
	//soundHandle_ = audio_->LoadAudio("resources/sound/get_2.wav");
}

void BuffItem::Update()
{
	ICharacter::Update();
	BoxCollider::Update(&worldTransform_);
}

void BuffItem::Draw(const ViewProjection& viewProjection)
{
	if (isHit_ == false)
	{
		ICharacter::Draw(viewProjection);
	}
}

void BuffItem::OnCollision(Collider* collider)
{
	if (collider->GetcollitionAttribute() == kCollitionAttributePlayer)
	{
		isHit_ = true;
		isActive_ = false;
		//audio_->Play(soundHandle_, 1, 0);
	}
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


