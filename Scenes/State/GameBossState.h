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
#include "GameObject/Character/Player/Player.h"
#include "GameObject/Character/Boss/Boss.h"
#include "GameObject/FollowCamera/FollowCamera.h"

#include "Base/ParticleSystem/Particle.h"

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

	std::unique_ptr<FollowCamera> followCamera;

	//地面
	std::unique_ptr<Model> groundModel_ = nullptr;
	std::unique_ptr<Ground> ground_;

	//天球
	std::unique_ptr<Skydome> skydome_;
	std::unique_ptr<Model> skydomeModel_;

	std::unique_ptr<Player> player;
	//プレイヤーモデル
	std::unique_ptr<Model> modelFighterBody_ = nullptr;
	std::unique_ptr<Model> modelFighterHead_ = nullptr;
	std::unique_ptr<Model> modelFighterL_arm_ = nullptr;
	std::unique_ptr<Model> modelFighterR_arm_ = nullptr;
	std::unique_ptr<Model> modelFighterWeapon = nullptr;

	std::unique_ptr<Boss> boss_;
	std::unique_ptr<Model> bossModel_;

	//
	WorldTransform worldTransform_;
	WorldTransform worldTransform_Sprite;
	ViewProjection viewProjection_;

	std::unique_ptr<Sprite> targetSprite_;
	WorldTransform sprite_Target_;
	uint32_t textureHandle_target_;

	//3Dオブジェクトたち

	std::unique_ptr<Particle> particle;
};

