#pragma once
#include "IgameState.h"
#include "MyEngine.h"
#include "ModelData.h"
#include "Audio.h"
#include "Input.h"
#include "Mesh.h"
#include "Sprite.h"
#include "Light.h"
#include "Sphere.h"
#include "TextureManager.h"
#include "Model.h"
#define DIRECTINPUT_VERSION 0x0800//DirectInputのバージョン指定
#include <dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Math_Structs.h"
#include "Base/Math/Quaternion/Quaternion.h"
#include "Base/Utility/CollisionManager.h"
#include "GameObject/Ground/Ground.h"
#include "GameObject/Skydome/Skydome.h"

class GameBossState : public GameState
{
public:
	void Initialize();
	void Update();
	void Draw();

private:
	//基本機能ズ
	MyEngine* myEngine = nullptr;
	TextureManager* textureManager_ = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	Light* light_ = nullptr;
	DirectXCommon* DirectX_ = nullptr;
	GlobalVariables* globalVariables = nullptr;
	std::unique_ptr<CollisionManager> collisionManager_;

	//地面
	std::unique_ptr<Model> groundModel_ = nullptr;
	std::unique_ptr<Ground> ground_;

	//天球
	std::unique_ptr<Skydome> skydome_;
	std::unique_ptr<Model> skydomeModel_;

	//
	WorldTransform worldTransform_;
	WorldTransform worldTransform_Sprite;
	ViewProjection viewProjection_;

	//3Dオブジェクトたち

	int time;
};
