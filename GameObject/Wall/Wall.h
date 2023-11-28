#pragma once
#include "Base/Model.h"
#include "Base/WorldTransform.h"
#include "Base/ViewProjection.h"

#include "GameObject/Character/ICharacter/ICharacter.h"
#include "GameObject/Character/Player/Player.h"
#include "Base/Utility/BoxCollider.h"
#include "Base/Utility/CollisionConfig.h"

class Wall : public ICharacter, public BoxCollider
{
public:
	Wall();
	~Wall();

	void Initalize(const std::vector<Model*>& models, Vector3 position);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	void OnCollision(Collider* collider)override;

	void SetScale(Vector3 scale);

	void SetPosition(Vector3 position);

private:

};


