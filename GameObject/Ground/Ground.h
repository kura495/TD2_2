#pragma once
#include "Base/Model.h"
#include "Base/WorldTransform.h"
#include "Base/ViewProjection.h"
#include "Base/Utility/BoxCollider.h"
#include "Base/Utility/CollisionConfig.h"

class Ground : public BoxCollider
{
public:
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void OnCollision(uint32_t collisionAttribute)override;

	void SetScale(Vector3 scale);

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;
};
