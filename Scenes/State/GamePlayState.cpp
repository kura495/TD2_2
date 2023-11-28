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
	ground_[0] = std::make_unique<Ground>();
	ground_[0]->Initalize(groundModels, { 0.0f,0.0f,260.0f });
	ground_[0]->SetScale({ 12.0f, 1.0f, 40.0f });

	ground_[1] = std::make_unique<Ground>();
	ground_[1]->Initalize(groundModels, { 0.0f,0.0f,570.0f });
	ground_[1]->SetScale({ 12.0f, 1.0f, 40.0f });

	//壁
	wallModel_.reset(Model::CreateModelFromObj("resources/Cube", "Cube.obj"));
	std::vector<Model*> wallModels = {
		wallModel_.get() };

	wallWorldTransform_[0].Initialize();

	//ステージ1枚目
	wallWorldTransform_[0].translation_ = { -55.0f,0.0f,40.0f };
	wallWorldTransform_[1].translation_ = { -40.0f,0.0f,46.0f };
	wallWorldTransform_[2].translation_ = { -40.0f,0.0f,66.0f };
	wallWorldTransform_[3].translation_ = { 45.0f,0.0f,75.0f };
	wallWorldTransform_[4].translation_ = { 56.0f,0.0f,90.0f };
	wallWorldTransform_[5].translation_ = { 37.0f,0.0f,95.0f };
	wallWorldTransform_[6].translation_ = { 0.0f,0.0f,170.0f };
	wallWorldTransform_[7].translation_ = { -30.0f,0.0f,200.0f };
	wallWorldTransform_[8].translation_ = { 30.0f,0.0f,200.0f };
	wallWorldTransform_[9].translation_ = { -45.0f,0.0f,280.0f };
	wallWorldTransform_[10].translation_ = { 45.0f,0.0f,280.0f };
	wallWorldTransform_[11].translation_ = { 0.0f,0.0f,320.0f };
	wallWorldTransform_[12].translation_ = { -19.0f,0.0f,340.0f };
	wallWorldTransform_[13].translation_ = { 0.0f,0.0f,440.0f };

	//画面端の壁
	wallWorldTransform_[14].translation_ = { 120.0f,0.0f,415.0f };
	wallWorldTransform_[15].translation_ = { -120.0f,0.0f,415.0f };
	wallWorldTransform_[16].translation_ = { 0.0f,0.0f, 970.0f };
	wallWorldTransform_[17].translation_ = { 0.0f,0.0f,-140.0f };

	//ステージ2枚目
	wallWorldTransform_[18].translation_ = { 53.0f,0.0f,530.0f };
	wallWorldTransform_[19].translation_ = { -53.0f,0.0f,530.0f };
	wallWorldTransform_[20].translation_ = { 0.0f,0.0f, 580.0f };
	wallWorldTransform_[21].translation_ = { 0.0f,0.0f, 675.0f };
	wallWorldTransform_[22].translation_ = { 0.0f,4.0f, 690.0f };
	wallWorldTransform_[23].translation_ = { 0.0f,0.0f, 705.0f };
	wallWorldTransform_[24].translation_ = { 30.0f,0.0f, 755.0f };
	wallWorldTransform_[25].translation_ = { 20.0f,4.0f, 765.0f };
	wallWorldTransform_[26].translation_ = { 10.0f,8.0f, 775.0f };
	wallWorldTransform_[27].translation_ = { 0.0f,12.0f, 785.0f };
	wallWorldTransform_[28].translation_ = { -10.0f,8.0f, 795.0f };
	wallWorldTransform_[29].translation_ = { -20.0f,4.0f, 805.0f };
	wallWorldTransform_[30].translation_ = { -30.0f,0.0f, 815.0f };

	//ステージ1枚目
	wall_[0] = std::make_unique<Wall>();
	wall_[0]->Initalize(wallModels, { wallWorldTransform_[0].translation_.x,wallWorldTransform_[0].translation_.y,wallWorldTransform_[0].translation_.z });
	wall_[0]->SetScale({ 18.0f, 10.0f, 3.0f });

	wall_[1] = std::make_unique<Wall>();
	wall_[1]->Initalize(wallModels, { wallWorldTransform_[1].translation_.x,wallWorldTransform_[1].translation_.y,wallWorldTransform_[1].translation_.z });
	wall_[1]->SetScale({ 3.0f, 10.0f, 3.0f });

	wall_[2] = std::make_unique<Wall>();
	wall_[2]->Initalize(wallModels, { wallWorldTransform_[2].translation_.x,wallWorldTransform_[2].translation_.y,wallWorldTransform_[2].translation_.z });
	wall_[2]->SetScale({ 3.0f, 10.0f, 3.0f });

	wall_[3] = std::make_unique<Wall>();
	wall_[3]->Initalize(wallModels, { wallWorldTransform_[3].translation_.x,wallWorldTransform_[3].translation_.y,wallWorldTransform_[3].translation_.z });
	wall_[3]->SetScale({ 8.0f, 10.0f, 3.0f });

	wall_[4] = std::make_unique<Wall>();
	wall_[4]->Initalize(wallModels, { wallWorldTransform_[4].translation_.x,wallWorldTransform_[4].translation_.y,wallWorldTransform_[4].translation_.z });
	wall_[4]->SetScale({ 3.0f, 10.0f, 18.0f });

	wall_[5] = std::make_unique<Wall>();
	wall_[5]->Initalize(wallModels, { wallWorldTransform_[5].translation_.x,wallWorldTransform_[5].translation_.y,wallWorldTransform_[5].translation_.z });
	wall_[5]->SetScale({ 3.0f, 10.0f, 3.0f });

	wall_[6] = std::make_unique<Wall>();
	wall_[6]->Initalize(wallModels, { wallWorldTransform_[6].translation_.x,wallWorldTransform_[6].translation_.y,wallWorldTransform_[6].translation_.z });
	wall_[6]->SetScale({ 3.0f, 10.0f, 3.0f });

	wall_[7] = std::make_unique<Wall>();
	wall_[7]->Initalize(wallModels, { wallWorldTransform_[7].translation_.x,wallWorldTransform_[7].translation_.y,wallWorldTransform_[7].translation_.z });
	wall_[7]->SetScale({ 3.0f, 10.0f, 3.0f });

	wall_[8] = std::make_unique<Wall>();
	wall_[8]->Initalize(wallModels, { wallWorldTransform_[8].translation_.x,wallWorldTransform_[8].translation_.y,wallWorldTransform_[8].translation_.z });
	wall_[8]->SetScale({ 3.0f, 10.0f, 3.0f });

	wall_[9] = std::make_unique<Wall>();
	wall_[9]->Initalize(wallModels, { wallWorldTransform_[9].translation_.x,wallWorldTransform_[9].translation_.y,wallWorldTransform_[9].translation_.z });
	wall_[9]->SetScale({ 20.0f, 10.0f, 3.0f });

	wall_[10] = std::make_unique<Wall>();
	wall_[10]->Initalize(wallModels, { wallWorldTransform_[10].translation_.x,wallWorldTransform_[10].translation_.y,wallWorldTransform_[10].translation_.z });
	wall_[10]->SetScale({ 20.0f, 10.0f, 3.0f });

	wall_[11] = std::make_unique<Wall>();
	wall_[11]->Initalize(wallModels, { wallWorldTransform_[11].translation_.x,wallWorldTransform_[11].translation_.y,wallWorldTransform_[11].translation_.z });
	wall_[11]->SetScale({ 3.0f, 10.0f, 17.0f });

	wall_[12] = std::make_unique<Wall>();
	wall_[12]->Initalize(wallModels, { wallWorldTransform_[12].translation_.x,wallWorldTransform_[12].translation_.y,wallWorldTransform_[12].translation_.z });
	wall_[12]->SetScale({ 22.0f, 10.0f, 3.0f });

	wall_[13] = std::make_unique<Wall>();
	wall_[13]->Initalize(wallModels, { wallWorldTransform_[13].translation_.x,wallWorldTransform_[13].translation_.y,wallWorldTransform_[13].translation_.z });
	wall_[13]->SetScale({ 3.0f, 10.0f, 20.0f });

	//画面端の壁
	wall_[14] = std::make_unique<Wall>();
	wall_[14]->Initalize(wallModels, { wallWorldTransform_[14].translation_.x,wallWorldTransform_[14].translation_.y,wallWorldTransform_[14].translation_.z });
	wall_[14]->SetScale({ 3.0f, 10.0f, 558.0f });

	wall_[15] = std::make_unique<Wall>();
	wall_[15]->Initalize(wallModels, { wallWorldTransform_[15].translation_.x,wallWorldTransform_[15].translation_.y,wallWorldTransform_[15].translation_.z });
	wall_[15]->SetScale({ 3.0f, 10.0f, 558.0f });

	wall_[16] = std::make_unique<Wall>();
	wall_[16]->Initalize(wallModels, { wallWorldTransform_[16].translation_.x,wallWorldTransform_[16].translation_.y,wallWorldTransform_[16].translation_.z });
	wall_[16]->SetScale({ 120.0f, 10.0f, 3.0f });

	wall_[17] = std::make_unique<Wall>();
	wall_[17]->Initalize(wallModels, { wallWorldTransform_[17].translation_.x,wallWorldTransform_[17].translation_.y,wallWorldTransform_[17].translation_.z });
	wall_[17]->SetScale({ 120.0f, 10.0f, 3.0f });

	//ステージ2枚目
	wall_[18] = std::make_unique<Wall>();
	wall_[18]->Initalize(wallModels, { wallWorldTransform_[18].translation_.x,wallWorldTransform_[18].translation_.y,wallWorldTransform_[18].translation_.z });
	wall_[18]->SetScale({ 12.0f, 10.0f, 3.0f });

	wall_[19] = std::make_unique<Wall>();
	wall_[19]->Initalize(wallModels, { wallWorldTransform_[19].translation_.x,wallWorldTransform_[19].translation_.y,wallWorldTransform_[19].translation_.z });
	wall_[19]->SetScale({ 12.0f, 10.0f, 3.0f });

	wall_[20] = std::make_unique<Wall>();
	wall_[20]->Initalize(wallModels, { wallWorldTransform_[20].translation_.x,wallWorldTransform_[20].translation_.y,wallWorldTransform_[20].translation_.z });
	wall_[20]->SetScale({ 5.0f, 10.0f, 3.0f });

	wall_[21] = std::make_unique<Wall>();
	wall_[21]->Initalize(wallModels, { wallWorldTransform_[21].translation_.x,wallWorldTransform_[21].translation_.y,wallWorldTransform_[21].translation_.z });
	wall_[21]->SetScale({ 8.0f, 2.0f, 8.0f });

	wall_[22] = std::make_unique<Wall>();
	wall_[22]->Initalize(wallModels, { wallWorldTransform_[22].translation_.x,wallWorldTransform_[22].translation_.y,wallWorldTransform_[22].translation_.z });
	wall_[22]->SetScale({ 8.0f, 2.0f, 8.0f });

	wall_[23] = std::make_unique<Wall>();
	wall_[23]->Initalize(wallModels, { wallWorldTransform_[23].translation_.x,wallWorldTransform_[23].translation_.y,wallWorldTransform_[23].translation_.z });
	wall_[23]->SetScale({ 8.0f, 2.0f, 8.0f });

	wall_[24] = std::make_unique<Wall>();
	wall_[24]->Initalize(wallModels, { wallWorldTransform_[24].translation_.x,wallWorldTransform_[24].translation_.y,wallWorldTransform_[24].translation_.z });
	wall_[24]->SetScale({ 8.0f, 2.0f, 5.0f });

	wall_[25] = std::make_unique<Wall>();
	wall_[25]->Initalize(wallModels, { wallWorldTransform_[25].translation_.x,wallWorldTransform_[25].translation_.y,wallWorldTransform_[25].translation_.z });
	wall_[25]->SetScale({ 8.0f, 2.0f, 5.0f });

	wall_[26] = std::make_unique<Wall>();
	wall_[26]->Initalize(wallModels, { wallWorldTransform_[26].translation_.x,wallWorldTransform_[26].translation_.y,wallWorldTransform_[26].translation_.z });
	wall_[26]->SetScale({ 8.0f, 2.0f, 5.0f });

	wall_[27] = std::make_unique<Wall>();
	wall_[27]->Initalize(wallModels, { wallWorldTransform_[27].translation_.x,wallWorldTransform_[27].translation_.y,wallWorldTransform_[27].translation_.z });
	wall_[27]->SetScale({ 8.0f, 2.0f, 5.0f });

	wall_[28] = std::make_unique<Wall>();
	wall_[28]->Initalize(wallModels, { wallWorldTransform_[28].translation_.x,wallWorldTransform_[28].translation_.y,wallWorldTransform_[28].translation_.z });
	wall_[28]->SetScale({ 8.0f, 2.0f, 5.0f });

	wall_[29] = std::make_unique<Wall>();
	wall_[29]->Initalize(wallModels, { wallWorldTransform_[29].translation_.x,wallWorldTransform_[29].translation_.y,wallWorldTransform_[29].translation_.z });
	wall_[29]->SetScale({ 8.0f, 2.0f, 5.0f });

	wall_[30] = std::make_unique<Wall>();
	wall_[30]->Initalize(wallModels, { wallWorldTransform_[30].translation_.x,wallWorldTransform_[30].translation_.y,wallWorldTransform_[30].translation_.z });
	wall_[30]->SetScale({ 8.0f, 2.0f, 5.0f });

	//バフアイテム
	buffItemModel_.reset(Model::CreateModelFromObj("resources/Item", "Item.obj"));
	std::vector<Model*> buffItemModels = {
		buffItemModel_.get() };

	buffItemWorldTransform_[0].Initialize();

	//ステージ1枚目
	buffItemWorldTransform_[0].translation_ = { -55.0f,3.0f,55.0f };
	buffItemWorldTransform_[1].translation_ = { 43.0f,3.0f,84.0f };
	buffItemWorldTransform_[2].translation_ = { 0.0f,3.0f,178.0f };
	buffItemWorldTransform_[3].translation_ = { -37.0f,3.0f,308.0f };
	buffItemWorldTransform_[4].translation_ = { -45.0f,3.0f,308.0f };
	buffItemWorldTransform_[5].translation_ = { -53.0f,3.0f,308.0f };

	buffItemWorldTransform_[6].translation_ = { 29.0f,3.0f,308.0f };
	buffItemWorldTransform_[7].translation_ = { 37.0f,3.0f,324.0f };
	buffItemWorldTransform_[8].translation_ = { 45.0f,3.0f,340.0f };
	buffItemWorldTransform_[9].translation_ = { 37.0f,3.0f,356.0f };
	buffItemWorldTransform_[10].translation_ = { 29.0f,3.0f,372.0f };

	buffItemWorldTransform_[11].translation_ = { -29.0f,3.0f,412.0f };
	buffItemWorldTransform_[12].translation_ = { -37.0f,3.0f,428.0f };
	buffItemWorldTransform_[13].translation_ = { -45.0f,3.0f,444.0f };
	buffItemWorldTransform_[14].translation_ = { -37.0f,3.0f,460.0f };
	buffItemWorldTransform_[15].translation_ = { -29.0f,3.0f,476.0f };

	//ワープ
	buffItemWorldTransform_[16].translation_ = { 0.0f,5.0f,900.0f };

	//ステージ2枚目
	buffItemWorldTransform_[17].translation_ = { 70.0f,3.0f,530.0f };
	buffItemWorldTransform_[18].translation_ = { -70.0f,3.0f,530.0f };
	buffItemWorldTransform_[19].translation_ = { 45.0f,3.0f,540.0f };
	buffItemWorldTransform_[20].translation_ = { -45.0f,3.0f,540.0f };
	buffItemWorldTransform_[21].translation_ = { 0.0f,3.0f,570.0f };
	buffItemWorldTransform_[22].translation_ = { 0.0f,13.0f,690.0f };

	buffItemWorldTransform_[23].translation_ = { 20.0f,13.0f, 760.0f };
	buffItemWorldTransform_[24].translation_ = { 10.0f,17.0f, 770.0f };
	buffItemWorldTransform_[25].translation_ = { 0.0f,21.0f,780.0f };
	buffItemWorldTransform_[26].translation_ = { -10.0f,17.0f,790.0f };
	buffItemWorldTransform_[27].translation_ = { -20.0f,13.0f,800.0f };

	buffItemWorldTransform_[28].translation_ = { 12.5f,3.0f,792.5f };
	buffItemWorldTransform_[29].translation_ = { 0.0f,3.0f,780.0f };
	buffItemWorldTransform_[30].translation_ = { -12.5f,3.0f,767.5f };

	buffItem_[16] = std::make_unique<BuffItem>();
	buffItem_[16]->Initalize(buffItemModels, { buffItemWorldTransform_[16].translation_.x, buffItemWorldTransform_[16].translation_.y, buffItemWorldTransform_[16].translation_.z });
	buffItem_[16]->SetScale({ 5.0f, 5.0f, 5.0f });
	buffItem_[16]->SetcollitionAttribute(kCollitionAttributeEnemy);
	buffItem_[16]->SetcollisionMask(kCollitionAttributeEnemy);

	for (int i = 0; i < 16; i++)
	{
		buffItem_[i] = std::make_unique<BuffItem>();
		buffItem_[i]->Initalize(buffItemModels, { buffItemWorldTransform_[i].translation_.x, buffItemWorldTransform_[i].translation_.y, buffItemWorldTransform_[i].translation_.z });
		buffItem_[i]->SetScale({ 3.0f, 3.0f, 3.0f });
	}

	for (int i = 17; i < 31; i++)
	{
		buffItem_[i] = std::make_unique<BuffItem>();
		buffItem_[i]->Initalize(buffItemModels, { buffItemWorldTransform_[i].translation_.x, buffItemWorldTransform_[i].translation_.y, buffItemWorldTransform_[i].translation_.z });
		buffItem_[i]->SetScale({ 3.0f, 3.0f, 3.0f });
	}

	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(skydomeModel_.get());

	player = std::make_unique<Player>();
	modelFighterBody_.reset(Model::CreateModelFromObj("resources/float_Body", "float_Body.obj"));
	modelFighterHead_.reset(Model::CreateModelFromObj("resources/float_Head", "float_Head.obj"));
	modelFighterL_arm_.reset(Model::CreateModelFromObj("resources/float_L_arm", "float_L_arm.obj"));
	modelFighterR_arm_.reset(Model::CreateModelFromObj("resources/float_R_arm", "float_R_arm.obj"));
	modelFighterWeapon_.reset(Model::CreateModelFromObj("resources/Cube", "Cube.obj"));
	std::vector<Model*> playerModels = {
		modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),modelFighterR_arm_.get(),modelFighterWeapon_.get(),
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
	for (int i = 0; i < 2; i++)
	{
		ground_[i]->Update();
	}

	for (int i = 0; i < 31; i++)
	{
		wall_[i]->Update();
	}

	for (int i = 0; i < 31; i++)
	{
		buffItem_[i]->Update();
	}

	//wall_[14]->SetPosition(wallWorldTransform_[14].translation_);

	skydome_->Updata();

	player->Update();

	followCamera->SetIsStickPre(player->GetIsStickRight(), player->GetIsStickLeft());

	followCamera->Update();
	viewProjection_ = followCamera->GetViewProjection();
	wallWorldTransform_[0].UpdateMatrix();
	buffItemWorldTransform_[0].UpdateMatrix();

	viewProjection_.UpdateMatrix();

	collisionManager_->AddBoxCollider(player.get());

	for (int i = 0; i < 2; i++)
	{
		collisionManager_->AddBoxCollider(ground_[i].get());
	}

	for (int i = 0; i < 31; i++)
	{
		collisionManager_->AddBoxCollider(wall_[i].get());
	}

	for (int i = 0; i < 31; i++)
	{
		collisionManager_->AddBoxCollider(buffItem_[i].get());
	}
	
	collisionManager_->CheckAllCollisions();
	collisionManager_->ClearCollider();

	if (player->GetIsDead() == true)
	{
		for (int i = 0; i < 31; i++)
		{
			player->SetIsDead(false);
			buffItem_[i]->SetIsHit(false);
		}
	}

	ImGui::Begin("Play");
	//ImGui::DragFloat3("itemWorldTransform", &wallWorldTransform_[14].translation_.x, 1.0f);
	ImGui::End();
}

void GamePlayState::Draw()
{
	//3Dモデル描画ここから
	
	for (int i = 0; i < 2; i++)
	{
		ground_[i]->Draw(viewProjection_);
	}

	for (int i = 0; i < 31; i++)
	{
		wall_[i]->Draw(viewProjection_);
	}

	for (int i = 0; i < 31; i++)
	{
		buffItem_[i]->Draw(viewProjection_);
	}

	//skydome_->Draw(viewProjection_);

	player->Draw(viewProjection_);

	//3Dモデル描画ここまで	

	//Sprite描画ここから


	//Sprite描画ここまで
	
	//描画ここまで
}
