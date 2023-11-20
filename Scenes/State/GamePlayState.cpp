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

	//地面
	groundModel_.reset(Model::CreateModelFromObj("resources/Ground", "Ground.obj"));
	std::vector<Model*> groundModels = {
		groundModel_.get() };
	ground_ = std::make_unique<Ground>();
	ground_->Initalize(groundModels, { 0.0f,0.0f,230.0f });
	ground_->SetScale({ 10.0f, 1.0f, 30.0f });

	//壁
	wallModel_.reset(Model::CreateModelFromObj("resources/Cube", "Cube.obj"));
	std::vector<Model*> wallModels = {
		wallModel_.get() };

	wall_[0] = std::make_unique<Wall>();
	wall_[0]->Initalize(wallModels, { -55.0f,0.0f,40.0f });
	wall_[0]->SetScale({ 18.0f, 3.0f, 3.0f });

	wall_[1] = std::make_unique<Wall>();
	wall_[1]->Initalize(wallModels, { -40.0f,0.0f,46.0f });
	wall_[1]->SetScale({ 3.0f, 3.0f, 3.0f });

	wall_[2] = std::make_unique<Wall>();
	wall_[2]->Initalize(wallModels, { -40.0f,0.0f,66.0f });
	wall_[2]->SetScale({ 3.0f, 3.0f, 3.0f });

	wall_[3] = std::make_unique<Wall>();
	wall_[3]->Initalize(wallModels, { 45.0f,0.0f,75.0f });
	wall_[3]->SetScale({ 8.0f, 3.0f, 3.0f });

	wall_[4] = std::make_unique<Wall>();
	wall_[4]->Initalize(wallModels, { 56.0f,0.0f,90.0f });
	wall_[4]->SetScale({ 3.0f, 3.0f, 18.0f });

	wall_[5] = std::make_unique<Wall>();
	wall_[5]->Initalize(wallModels, { 37.0f,0.0f,95.0f });
	wall_[5]->SetScale({ 3.0f, 3.0f, 3.0f });

	wall_[6] = std::make_unique<Wall>();
	wall_[6]->Initalize(wallModels, { 0.0f,0.0f,170.0f });
	wall_[6]->SetScale({ 3.0f, 3.0f, 3.0f });

	wall_[7] = std::make_unique<Wall>();
	wall_[7]->Initalize(wallModels, { -30.0f,0.0f,200.0f });
	wall_[7]->SetScale({ 3.0f, 3.0f, 3.0f });

	wall_[8] = std::make_unique<Wall>();
	wall_[8]->Initalize(wallModels, { 30.0f,0.0f,200.0f });
	wall_[8]->SetScale({ 3.0f, 3.0f, 3.0f });

	wall_[9] = std::make_unique<Wall>();
	wall_[9]->Initalize(wallModels, { -45.0f,0.0f,280.0f });
	wall_[9]->SetScale({ 20.0f, 3.0f, 3.0f });

	wall_[10] = std::make_unique<Wall>();
	wall_[10]->Initalize(wallModels, { 45.0f,0.0f,280.0f });
	wall_[10]->SetScale({ 20.0f, 3.0f, 3.0f });

	wall_[11] = std::make_unique<Wall>();
	wall_[11]->Initalize(wallModels, { 0.0f,0.0f,320.0f });
	wall_[11]->SetScale({ 3.0f, 3.0f, 17.0f });

	wall_[12] = std::make_unique<Wall>();
	wall_[12]->Initalize(wallModels, { -19.0f,0.0f,340.0f });
	wall_[12]->SetScale({ 22.0f, 3.0f, 3.0f });

	wall_[13] = std::make_unique<Wall>();
	wall_[13]->Initalize(wallModels, { 0.0f,0.0f,440.0f });
	wall_[13]->SetScale({ 3.0f, 3.0f, 20.0f });

	//バフアイテム
	buffItemModel_.reset(Model::CreateModelFromObj("resources/Item", "Item.obj"));
	std::vector<Model*> buffItemModels = {
		buffItemModel_.get() };

	itemWorldTransform_[0].translation_ = { -55.0f,3.0f,55.0f };
	itemWorldTransform_[1].translation_ = { 43.0f,3.0f,84.0f };
	itemWorldTransform_[2].translation_ = { 0.0f,3.0f,178.0f };
	itemWorldTransform_[3].translation_ = { -37.0f,3.0f,308.0f };
	itemWorldTransform_[4].translation_ = { -45.0f,3.0f,308.0f };
	itemWorldTransform_[5].translation_ = { -53.0f,3.0f,308.0f };

	itemWorldTransform_[6].translation_ = { 29.0f,3.0f,308.0f };
	itemWorldTransform_[7].translation_ = { 37.0f,3.0f,324.0f };
	itemWorldTransform_[8].translation_ = { 45.0f,3.0f,340.0f };
	itemWorldTransform_[9].translation_ = { 37.0f,3.0f,356.0f };
	itemWorldTransform_[10].translation_ = { 29.0f,3.0f,372.0f };

	itemWorldTransform_[11].translation_ = { -29.0f,3.0f,412.0f };
	itemWorldTransform_[12].translation_ = { -37.0f,3.0f,428.0f };
	itemWorldTransform_[13].translation_ = { -45.0f,3.0f,444.0f };
	itemWorldTransform_[14].translation_ = { -37.0f,3.0f,460.0f };
	itemWorldTransform_[15].translation_ = { -29.0f,3.0f,476.0f };

	for (int i = 0; i < 16; i++)
	{
		buffItem_[i] = std::make_unique<BuffItem>();
		buffItem_[i]->Initalize(buffItemModels, { itemWorldTransform_[i].translation_.x, itemWorldTransform_[i].translation_.y, itemWorldTransform_[i].translation_.z });
		buffItem_[i]->SetScale({ 3.0f, 3.0f, 3.0f });
	}

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

	for (int i = 0; i < 14; i++)
	{
		wall_[i]->Update();
	}

	for (int i = 0; i < 16; i++)
	{
		buffItem_[i]->Update();
	}

	buffItem_[11]->SetPosition(itemWorldTransform_[11].translation_);

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

	for (int i = 0; i < 16; i++)
	{
		collisionManager_->AddBoxCollider(buffItem_[i].get());
	}
	
	collisionManager_->CheckAllCollisions();
	collisionManager_->ClearCollider();

	ImGui::Begin("Play");
	ImGui::DragFloat3("itemWorldTransform", &itemWorldTransform_[6].translation_.x, 1.0f);
	ImGui::End();
}

void GamePlayState::Draw()
{
	//3Dモデル描画ここから
	
	ground_->Draw(viewProjection_);

	for (int i = 0; i < 14; i++)
	{
		wall_[i]->Draw(viewProjection_);
	}

	for (int i = 0; i < 16; i++)
	{
		buffItem_[i]->Draw(viewProjection_);
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
