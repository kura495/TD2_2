#pragma once
#include "Base/Model.h"
#include "Base/WorldTransform.h"
#include "Base/ViewProjection.h"
#include "Base/Audio/Audio.h"

#include "GameObject/Character/ICharacter/ICharacter.h"
#include "GameObject/Character/Player/Player.h"
#include "Base/Utility/BoxCollider.h"
#include "Base/Utility/CollisionConfig.h"

class BuffItem : public ICharacter, public BoxCollider
{
public:
	BuffItem();
	~BuffItem();

	void Initalize(const std::vector<Model*>& models, Vector3 position);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	void OnCollision(Collider* collider)override;

	void SetScale(Vector3 scale);

	void SetPosition(Vector3 position);

    void SetIsHit(bool isHit) { isHit_ = isHit; }

	bool GetIsActive() { return isActive_; }

private:
	Audio* audio_ = nullptr;

	uint32_t soundHandle_;

	bool isHit_ = false;

	bool isActive_ = false;
};

