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

	ground_[2] = std::make_unique<Ground>();
	ground_[2]->Initalize(groundModels, { -240.0f,0.0f,260.0f });
	ground_[2]->SetScale({ 12.0f, 1.0f, 40.0f });

	ground_[3] = std::make_unique<Ground>();
	ground_[3]->Initalize(groundModels, { -240.0f,0.0f,570.0f });
	ground_[3]->SetScale({ 12.0f, 1.0f, 40.0f });

	//壁
	wallModel_.reset(Model::CreateModelFromObj("resources/Cube", "Cube.obj"));
	std::vector<Model*> wallModels = {
		wallModel_.get() };

	/*edgeWallModel_.reset(Model::CreateModelFromObj("resources/Wall", "Wall.obj"));
	std::vector<Model*> edgeWallModels = {
		edgeWallModel_.get() };*/

	for (int i = 0; i < 6; i++)
	{
		wallWorldTransform_[i].Initialize();
	}

	////画面端の壁
	wallWorldTransform_[0].translation_ = { 120.0f,0.0f,415.0f };
	wallWorldTransform_[1].translation_ = { -360.0f,0.0f,415.0f };
	wallWorldTransform_[2].translation_ = { -115.0f,0.0f, 970.0f };
	wallWorldTransform_[3].translation_ = { -115.0f,0.0f,-140.0f };

	wallWorldTransform_[4].translation_ = { 70.0f,0.0f,600.0f };
	wallWorldTransform_[5].translation_ = { -70.0f,0.0f,300.0f };
	wallWorldTransform_[6].translation_ = { -230.0f,0.0f,250.0f };
	wallWorldTransform_[7].translation_ = { -140.0f,0.0f,700.0f };

	////画面端の壁
	wall_[0] = std::make_unique<Wall>();
	wall_[0]->Initalize(wallModels, { wallWorldTransform_[0].translation_.x,wallWorldTransform_[0].translation_.y,wallWorldTransform_[0].translation_.z });
	wall_[0]->SetScale({ 3.0f, 10.0f, 558.0f });

	wall_[1] = std::make_unique<Wall>();
	wall_[1]->Initalize(wallModels, { wallWorldTransform_[1].translation_.x,wallWorldTransform_[1].translation_.y,wallWorldTransform_[1].translation_.z });
	wall_[1]->SetScale({ 3.0f, 10.0f, 558.0f });

	wall_[2] = std::make_unique<Wall>();
	wall_[2]->Initalize(wallModels, { wallWorldTransform_[2].translation_.x,wallWorldTransform_[2].translation_.y,wallWorldTransform_[2].translation_.z });
	wall_[2]->SetScale({ 260.0f, 10.0f, 3.0f });

	wall_[3] = std::make_unique<Wall>();
	wall_[3]->Initalize(wallModels, { wallWorldTransform_[3].translation_.x,wallWorldTransform_[3].translation_.y,wallWorldTransform_[3].translation_.z });
	wall_[3]->SetScale({ 260.0f, 10.0f, 3.0f });


	wall_[4] = std::make_unique<Wall>();
	wall_[4]->Initalize(wallModels, { wallWorldTransform_[4].translation_.x,wallWorldTransform_[4].translation_.y,wallWorldTransform_[4].translation_.z });
	wall_[4]->SetScale({ 50.0f, 10.0f, 3.0f });

	wall_[5] = std::make_unique<Wall>();
	wall_[5]->Initalize(wallModels, { wallWorldTransform_[5].translation_.x,wallWorldTransform_[5].translation_.y,wallWorldTransform_[5].translation_.z });
	wall_[5]->SetScale({ 10.0f, 10.0f, 45.0f });

	wall_[6] = std::make_unique<Wall>();
	wall_[6]->Initalize(wallModels, { wallWorldTransform_[6].translation_.x,wallWorldTransform_[6].translation_.y,wallWorldTransform_[6].translation_.z });
	wall_[6]->SetScale({ 30.0f, 10.0f, 30.0f });

	wall_[7] = std::make_unique<Wall>();
	wall_[7]->Initalize(wallModels, { wallWorldTransform_[7].translation_.x,wallWorldTransform_[7].translation_.y,wallWorldTransform_[7].translation_.z });
	wall_[7]->SetScale({ 45.0f, 10.0f, 10.0f });

	//バフアイテム
	buffItemModel_.reset(Model::CreateModelFromObj("resources/speedUP", "speedUP.obj"));
	std::vector<Model*> buffItemModels = {
		buffItemModel_.get() };

	/*for (int i = 0; i < 5; i++)
	{
		buffItemWorldTransform_[i].Initialize();
	}*/

	buffItemWorldTransform_[0].translation_ = { 0.0f,3.0f,40.0f };
	buffItemWorldTransform_[1].translation_ = { -230.0f,3.0f,200.0f };
	buffItemWorldTransform_[2].translation_ = { -230.0f,3.0f,300.0f };
	buffItemWorldTransform_[3].translation_ = { -180.0f,3.0f,250.0f };
	buffItemWorldTransform_[4].translation_ = { -180.0f,3.0f,250.0f };
	/*buffItemWorldTransform_[5].translation_ = { -53.0f,3.0f,308.0f };*/

	/*buffItemWorldTransform_[6].translation_ = { 29.0f,3.0f,308.0f };
	buffItemWorldTransform_[7].translation_ = { 37.0f,3.0f,324.0f };
	buffItemWorldTransform_[8].translation_ = { 45.0f,3.0f,340.0f };
	buffItemWorldTransform_[9].translation_ = { 37.0f,3.0f,356.0f };
	buffItemWorldTransform_[10].translation_ = { 29.0f,3.0f,372.0f };

	buffItemWorldTransform_[11].translation_ = { -29.0f,3.0f,412.0f };
	buffItemWorldTransform_[12].translation_ = { -37.0f,3.0f,428.0f };
	buffItemWorldTransform_[13].translation_ = { -45.0f,3.0f,444.0f };
	buffItemWorldTransform_[14].translation_ = { -37.0f,3.0f,460.0f };
	buffItemWorldTransform_[15].translation_ = { -29.0f,3.0f,476.0f };*/

	////ワープ
	//buffItemWorldTransform_[16].translation_ = { 0.0f,5.0f,900.0f };

	////ステージ2枚目
	//buffItemWorldTransform_[17].translation_ = { 70.0f,3.0f,530.0f };
	//buffItemWorldTransform_[18].translation_ = { -70.0f,3.0f,530.0f };
	//buffItemWorldTransform_[19].translation_ = { 45.0f,3.0f,540.0f };
	//buffItemWorldTransform_[20].translation_ = { -45.0f,3.0f,540.0f };
	//buffItemWorldTransform_[21].translation_ = { 0.0f,3.0f,570.0f };
	//buffItemWorldTransform_[22].translation_ = { 0.0f,13.0f,690.0f };

	//buffItemWorldTransform_[23].translation_ = { 20.0f,13.0f, 760.0f };
	//buffItemWorldTransform_[24].translation_ = { 10.0f,17.0f, 770.0f };
	//buffItemWorldTransform_[25].translation_ = { 0.0f,21.0f,780.0f };
	//buffItemWorldTransform_[26].translation_ = { -10.0f,17.0f,790.0f };
	//buffItemWorldTransform_[27].translation_ = { -20.0f,13.0f,800.0f };

	//buffItemWorldTransform_[28].translation_ = { 12.5f,3.0f,792.5f };
	//buffItemWorldTransform_[29].translation_ = { 0.0f,3.0f,780.0f };
	//buffItemWorldTransform_[30].translation_ = { -12.5f,3.0f,767.5f };

	//buffItem_[16] = std::make_unique<BuffItem>();
	//buffItem_[16]->Initalize(buffItemModels, { buffItemWorldTransform_[16].translation_.x, buffItemWorldTransform_[16].translation_.y, buffItemWorldTransform_[16].translation_.z });
	//buffItem_[16]->SetScale({ 5.0f, 5.0f, 5.0f });
	//buffItem_[16]->SetcollitionAttribute(kCollitionAttributeGoal);
	//buffItem_[16]->SetcollisionMask(kCollitionAttributeGoal);

	for (int i = 0; i < 5; i++)
	{
		buffItem_[i] = std::make_unique<BuffItem>();
		buffItem_[i]->Initalize(buffItemModels, { buffItemWorldTransform_[i].translation_.x, buffItemWorldTransform_[i].translation_.y, buffItemWorldTransform_[i].translation_.z });
		buffItem_[i]->SetScale({ 3.0f, 3.0f, 3.0f });
	}

	//for (int i = 17; i < 31; i++)
	//{
	//	buffItem_[i] = std::make_unique<BuffItem>();
	//	buffItem_[i]->Initalize(buffItemModels, { buffItemWorldTransform_[i].translation_.x, buffItemWorldTransform_[i].translation_.y, buffItemWorldTransform_[i].translation_.z });
	//	buffItem_[i]->SetScale({ 3.0f, 3.0f, 3.0f });
	//}

	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(skydomeModel_.get());

	player = std::make_unique<Player>();
	modelFighterBody_.reset(Model::CreateModelFromObj("resources/float_Body", "float_Body.obj"));
	modelFighterHead_.reset(Model::CreateModelFromObj("resources/float_Head", "float_Head.obj"));
	modelFighterL_arm_.reset(Model::CreateModelFromObj("resources/float_L_arm", "float_L_arm.obj"));
	modelFighterR_arm_.reset(Model::CreateModelFromObj("resources/float_R_arm", "float_R_arm.obj"));
	modelFighterWeapon.reset(Model::CreateModelFromObj("resources/arrow", "arrow.obj"));
	std::vector<Model*> playerModels = {
		modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),modelFighterR_arm_.get(),modelFighterWeapon.get(),
	};
	player->Initialize(playerModels);
	player->SetScale({ 3.0f, 3.0f, 3.0f });

	followCamera = std::make_unique<FollowCamera>();
	followCamera->Initalize();
	followCamera->SetTarget(&player->GetWorldTransform());
	player->SetViewProjection(&followCamera->GetViewProjection());

	joyStatePre = joyState;

	isPause_ = false;

	timers_.clear();
	for (uint32_t i = 0; i < 3; i++) {
		Timer* timer = new Timer();
		timer->Initialize(static_cast<Timer::DigitPlace>(i), 60, Vector3{ 1200.0f - float(i) * 30.0f, 10.0f, 0.0f });
		timers_.emplace_back(timer);

	}

	pause_ = std::make_unique<Pause>();
	pause_->Initialize();

	targetSprite_ = std::make_unique<Sprite>();
	targetSprite_->Initialize(Vector4{ 0.0f, 0.0f, 0.0f, 1.0f }, Vector4{ 0.0f, 128.0f, 0.0f, 1.0f }, Vector4{ 512.0f, 0.0f, 0.0f, 1.0f }, Vector4{ 512.0f, 128.0f, 0.0f, 1.0f });
	sprite_Target_.Initialize();
	sprite_Target_.translation_ = Vector3{ 384.0f, 598.0f, 0.0f };
	sprite_Target_.UpdateMatrix();
	textureHandle_target_ = textureManager_->LoadTexture("resources/Target/itemTarget.png");

	itemGaugeSprites_.clear();
	for (int i = 0; i < 3; i++) {
		Sprite* sprite = new Sprite();
		sprite->Initialize(Vector4{ 0.0f, 0.0f, 0.0f, 1.0f }, Vector4{ 0.0f, 128.0f, 0.0f, 1.0f }, Vector4{ 256.0f, 0.0f, 0.0f, 1.0f }, Vector4{ 256.0f, 128.0f, 0.0f, 1.0f });
		itemGaugeSprites_.emplace_back(sprite);
		worldTransform_itemGauge_[i].Initialize();
		worldTransform_itemGauge_[i].scale_ = Vector3{0.5f, 0.5f, 1.0f};
		worldTransform_itemGauge_[i].translation_ = Vector3{120.0f *float(i), 50.0f, 1.0f };
		worldTransform_itemGauge_[i].UpdateMatrix();
	}

	
	itemSprite_ = std::make_unique<Sprite>();
	itemSprite_->Initialize(Vector4{ 0.0f, 0.0f, 0.0f, 1.0f }, Vector4{ 0.0f, 64.0f, 0.0f, 1.0f }, Vector4{ 64.0f, 0.0f, 0.0f, 1.0f }, Vector4{ 64.0f, 64.0f, 0.0f, 1.0f });

	speedSprite_ = std::make_unique<Sprite>();
	speedSprite_->Initialize(Vector4{ 0.0f, 0.0f, 0.0f, 1.0f }, Vector4{ 0.0f, 128.0f, 0.0f, 1.0f }, Vector4{ 600.0f, 0.0f, 0.0f, 1.0f }, Vector4{ 600.0f, 128.0f, 0.0f, 1.0f });

	worldTransform_item_.Initialize();
	worldTransform_item_.scale_ = Vector3{ 1.8f, 0.75f, 1.0f };
	worldTransform_item_.translation_ = Vector3{ 5.0f, 58.0f, 1.0f };
	worldTransform_item_.UpdateMatrix();

	worldTransform_speed_.Initialize();
	worldTransform_speed_.scale_ = Vector3{ 0.8f, 0.8f, 1.0f };
	worldTransform_speed_.translation_ = Vector3{ -100.0f, -20.0f, 1.0f };
	worldTransform_speed_.UpdateMatrix();

	textureHandle_item_[0] = TextureManager::GetInstance()->LoadTexture("resources/ItemCount/gauge.png");
	textureHandle_item_[1] = TextureManager::GetInstance()->LoadTexture("resources/Item/ItemColor.png");
	textureHandle_item_[2] = TextureManager::GetInstance()->LoadTexture("resources/Item/speed.png");
}

void GamePlayState::Update()
{
	input->GetJoystickState(0, joyState);

	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_START && !(joyStatePre.Gamepad.wButtons & XINPUT_GAMEPAD_START))
	{
		if (!pauseRelease_)
		{
			isPause_ = !isPause_; 
			pauseRelease_ = true; 
		}
		pause_->SetIsTutorial(false);

	} else {
		pauseRelease_ = false; 
	}

	if (isPause_ == false)
	{
		for (int i = 0; i < 4; i++)
		{
			ground_[i]->Update();
		}

		for (int i = 0; i < 8; i++)
		{
			wall_[i]->Update();
		}

		for (int i = 0; i < 5; i++)
		{
			buffItem_[i]->Update();
		}

		/*wall_[15]->SetPosition(wallWorldTransform_[15].translation_);*/

		/*wall_[15]->SetRotation({ 0.0f, 45.0f, 0.0f });*/

		skydome_->Updata();

		player->Update();

		followCamera->SetIsStickPre(player->GetIsStickRight(), player->GetIsStickLeft());
		ImGui::Begin("Camera");
		ImGui::SliderFloat("FOV", &FOV, 0.0f, 120.0f);
		ImGui::End();
		followCamera->SetFOV(FOV);
		followCamera->Update();
		viewProjection_ = followCamera->GetViewProjection();
		for (int i = 0; i < 6; i++)
		{
			wallWorldTransform_[i].UpdateMatrix();
		}

		/*for (int i = 0; i < 5; i++)
		{
			buffItemWorldTransform_[i].UpdateMatrix();
		}*/

		viewProjection_.UpdateMatrix();

		collisionManager_->AddBoxCollider(player.get());

		for (int i = 0; i < 4; i++)
		{
			collisionManager_->AddBoxCollider(ground_[i].get());
		}

		for (int i = 0; i < 8; i++)
		{
			collisionManager_->AddBoxCollider(wall_[i].get());
		}

		for (auto& item : buffItem_) {
			if (item->GetIsActive()) {
				collisionManager_->AddBoxCollider(item.get());
			}
			
		}

		for (int i = 0; i < 5; i++)
		{

			collisionManager_->AddBoxCollider(buffItem_[i].get());
		}

		collisionManager_->CheckAllCollisions();
		collisionManager_->ClearCollider();

		if (player->GetIsGoal() == true)
		{

			for (int i = 0; i < 5; i++)
			{
				player->SetIsDead(false);
				buffItem_[i]->SetIsHit(false);
			}

			StateNo = 2;


			ImGui::Begin("Hit");
			//ImGui::Text("%d", StateNo);
			//ImGui::DragFloat3("itemWorldTransform", &itemWorldTransform_[6].translation_.x, 1.0f);
			ImGui::End();
		}

		ImGui::Begin("Play");


		/*ImGui::DragFloat3("itemWorldTransform", &wallWorldTransform_[15].translation_.x, 1.0f);*/
		/*ImGui::DragFloat3("itemWorldTransform", &wallWorldTransform_[15].rotation_.x, 1.0f);*/

		ImGui::End();

		for (auto& timer : timers_) {
			timer->Update();
		}

		

		worldTransform_item_.scale_.x = player->GetItemCount() * 0.374f;
		worldTransform_item_.UpdateMatrix();

	}
	else {
		ImGui::Begin("Pause");
		ImGui::Text("Title :  B Buttun");
		ImGui::Text("GamePlay : Start Buttun");
		ImGui::End();

		if (pause_->GetLeft()) {
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				StateNo = 0;
			}
		}

		pause_->Update();
	}

	joyStatePre = joyState;
}
	

void GamePlayState::Draw()
{
	//3Dモデル描画ここから
	
	for (int i = 0; i < 4; i++)
	{
		ground_[i]->Draw(viewProjection_);
	}

	for (int i = 0; i < 8; i++)
	{
		wall_[i]->Draw(viewProjection_);
	}

	for (int i = 0; i < 5; i++)
	{
		buffItem_[i]->Draw(viewProjection_);
	}

	skydome_->Draw(viewProjection_);

	player->Draw(viewProjection_);

	//3Dモデル描画ここまで	

	//Sprite描画ここから
	for (auto& timer : timers_) {
		timer->Draw();
	}

	speedSprite_->Draw(worldTransform_speed_, textureHandle_item_[2]);

	itemSprite_->Draw(worldTransform_item_, textureHandle_item_[1]);
	for (int i = 0; auto& sprite : itemGaugeSprites_) {
		sprite->Draw(worldTransform_itemGauge_[i], textureHandle_item_[0]);
		i++;
	}
	

	targetSprite_->Draw(sprite_Target_, textureHandle_target_);

	if (isPause_) {
		pause_->Draw();
	}

	//Sprite描画ここまで
	
	//描画ここまで
}
