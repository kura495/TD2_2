#include "Scenes/State/GamePlayState.h"

void GamePlayState::Initialize()
{
	input = Input::GetInstance();
	audio = Audio::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	light_ = Light::GetInstance();

	DirectX_ = DirectXCommon::GetInstance();

	collisionManager_ = std::make_unique<CollisionManager>();

	viewProjection_.Initialize();
	worldTransform_.Initialize();

	skydomeModel_.reset(Model::CreateModelFromObj("resources/skydome", "skydome.obj"));

	groundModel_.reset(Model::CreateModelFromObj("resources/Ground", "Ground.obj"));
	std::vector<Model*> groundModels = {
		groundModel_.get() };
	ground_ = std::make_unique<Ground>();
	ground_->Initalize(groundModels, { 0.0f,0.0f,230.0f });
	ground_->SetScale({ 10.0f, 1.0f, 30.0f });

	wallModel_.reset(Model::CreateModelFromObj("resources/Cube", "Cube.obj"));
	std::vector<Model*> wallModels = {
		wallModel_.get() };

	//壁
	wall_[0] = std::make_unique<Wall>();
	wall_[0]->Initalize(wallModels, { -55.0f,0.0f,40.0f });
	wall_[0]->SetScale({ 18.0f, 3.0f, 3.0f });

	wall_[1] = std::make_unique<Wall>();
	wall_[1]->Initalize(wallModels, { -40.0f,0.0f,46.0f });
	wall_[1]->SetScale({ 3.0f, 3.0f, 3.0f });

	wall_[2] = std::make_unique<Wall>();
	wall_[2]->Initalize(wallModels, { -40.0f,0.0f,66.0f });
	wall_[2]->SetScale({ 3.0f, 3.0f, 3.0f });

	/*ground2_ = std::make_unique<Ground>();
	ground2_->Initalize(PlaneModels, { 0.0f, 0.0f, 30.0f });
	ground3_ = std::make_unique<Ground>();
	ground3_->Initalize(PlaneModels, { 10.0f, 0.0f, 20.0f });*/

	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(skydomeModel_.get());

	player = std::make_unique<Player>();
	modelFighterBody_.reset(Model::CreateModelFromObj("resources/float_Body", "float_Body.obj"));
	modelFighterHead_.reset(Model::CreateModelFromObj("resources/float_Head", "float_Head.obj"));
	modelFighterL_arm_.reset(Model::CreateModelFromObj("resources/float_L_arm", "float_L_arm.obj"));
	modelFighterR_arm_.reset(Model::CreateModelFromObj("resources/float_R_arm", "float_R_arm.obj"));
	std::vector<Model*> playerModels = {
		modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),modelFighterR_arm_.get(),
	};
	player->Initialize(playerModels);
	player->SetScale({ 3.0f, 3.0f, 3.0f });

	followCamera = std::make_unique<FollowCamera>();
	followCamera->Initalize();
	followCamera->SetTarget(&player->GetWorldTransform());
	player->SetViewProjection(&followCamera->GetViewProjection());
}

void GamePlayState::Update()
{
	ground_->Update();
	/*ground2_->Update();
	ground3_->Update();*/

	for (int i = 0; i < 3; i++)
	{
		wall_[i]->Update();
	}

	skydome_->Updata();

	player->Update();

	followCamera->Update();
	viewProjection_ = followCamera->GetViewProjection();

	viewProjection_.UpdateMatrix();

	collisionManager_->AddBoxCollider(player.get());
	collisionManager_->AddBoxCollider(ground_.get());

	for (int i = 0; i < 3; i++)
	{
		collisionManager_->AddBoxCollider(wall_[i].get());
	}
	
	collisionManager_->CheckAllCollisions();
	collisionManager_->ClearCollider();

	ImGui::Begin("Play");

	ImGui::End();
}

void GamePlayState::Draw()
{
	//3Dモデル描画ここから
	
	ground_->Draw(viewProjection_);
	/*ground2_->Draw(viewProjection_);
	ground3_->Draw(viewProjection_);*/

	for (int i = 0; i < 3; i++)
	{
		wall_[i]->Draw(viewProjection_);
	}

	//skydome_->Draw(viewProjection_);

	player->Draw(viewProjection_);

	//3Dモデル描画ここまで	

	//1. ビット演算を取り回しの良いUtilityクラスにする
	//2. 三項演算子をつかって、構造がわかりやすいようにする
	//piplineStatus->GetIsMesh2() ? mesh2->Draw() : ;
	//piplineStatus->GetIsSprite() ? sprite->Draw() : ;
	//piplineStatus->SetAllFlags();
	//void PipelineStatu::SetAllFlags() {
	//	bit = 0x111111111111.....;
	//}
	//void PipelineStatus::ResetAllFlags() {
		//Ethna
	//	bit = 0;
	//}

	//Sprite描画ここから


	//Sprite描画ここまで
	
	//描画ここまで
}
