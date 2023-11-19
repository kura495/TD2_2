#pragma once
#include "Base/Model.h"
#include "Base/WorldTransform.h"
#include "Base/ViewProjection.h"

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

	void OnCollision(uint32_t collisionAttribute)override;

	void SetScale(Vector3 scale);

private:

};

