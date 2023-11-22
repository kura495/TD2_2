#pragma once
#include "IgameState.h"
#include "MyEngine.h"
#include "ModelData.h"
#include "Audio.h"
#include "Input.h"
#include "Base/Primitive/Mesh/Mesh.h"
#include "Sprite.h"
#include "Light.h"
#include "Base/Primitive/Sphere/Sphere.h"
#include "TextureManager.h"
#include "Model.h"
#include "Base/Renderer/Renderer.h"
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
#include "GameObject/Wall/Wall.h"
#include "GameObject/BuffItem/BuffItem.h"
#include "GameObject/Skydome/Skydome.h"
#include "GameObject/Character/Player/Player.h"
#include "GameObject/FollowCamera/FollowCamera.h"

#include "Base/ParticleSystem/Particle.h"

class GamePlayState :public GameState
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
	Audio* audio=nullptr;
	Light* light_ = nullptr;
	DirectXCommon* DirectX_ = nullptr;
	GlobalVariables* globalVariables = nullptr;
	

	ViewProjection viewProjection_;

	Renderer* renderer_;

	std::unique_ptr<Particle> particle;
};