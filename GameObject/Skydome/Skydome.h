#pragma once
#include "Base/Model.h"
#include "Base/WorldTransform.h"
#include "Base/ViewProjection.h"

class Skydome
{
public:
	void Initialize(Model* model);

	void Updata();

	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;
};

