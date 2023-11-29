#include "Scenes/State/GameBossState.h"

void GameBossState::Initialize()
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

	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(skydomeModel_.get());

	//地面
	groundModel_.reset(Model::CreateModelFromObj("resources/Ground", "Ground.obj"));
	std::vector<Model*> groundModels = {
		groundModel_.get() };
	ground_ = std::make_unique<Ground>();
	ground_->Initalize(groundModels, { 0.0f,0.0f,0.0f });
	ground_->SetScale({ 18.0f, 1.0f, 18.0f });

	player = std::make_unique<Player>();
	modelFighterBody_.reset(Model::CreateModelFromObj("resources/float_Body", "float_Body.obj"));
	modelFighterHead_.reset(Model::CreateModelFromObj("resources/float_Head", "float_Head.obj"));
	modelFighterL_arm_.reset(Model::CreateModelFromObj("resources/float_L_arm", "float_L_arm.obj"));
	modelFighterR_arm_.reset(Model::CreateModelFromObj("resources/float_R_arm", "float_R_arm.obj"));
	modelFighterWeapon.reset(Model::CreateModelFromObj("resources/arrow", "arrow.obj"));
	std::vector<Model*> playerModels = {
		modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),modelFighterR_arm_.get(), modelFighterWeapon.get(),
	};
	player->Initialize(playerModels);
	player->SetScale({ 3.0f, 3.0f, 3.0f });

	bossModel_.reset(Model::CreateModelFromObj("resources/Boss", "Boss.obj"));
	std::vector<Model*> bossModels = {
		bossModel_.get() };

	boss_ = std::make_unique<Boss>();
	boss_->SetPlayer(player.get());
	boss_->Initialize(bossModels);
	boss_->SetScale({ 8.0f, 8.0f, 8.0f });

	player->SetBoss(boss_.get());


	followCamera = std::make_unique<FollowCamera>();
	followCamera->Initalize();
	followCamera->SetTarget(&player->GetWorldTransform());
	player->SetViewProjection(&followCamera->GetViewProjection());



	particle = std::make_unique<Particle>();
	particle->Initalize(10, "resources/circle.png");

	targetSprite_ = std::make_unique<Sprite>();
	targetSprite_->Initialize(Vector4{ 0.0f, 0.0f, 0.0f, 1.0f }, Vector4{ 0.0f, 128.0f, 0.0f, 1.0f }, Vector4{ 600.0f, 0.0f, 0.0f, 1.0f }, Vector4{ 600.0f, 128.0f, 0.0f, 1.0f });
	sprite_Target_.Initialize();
	sprite_Target_.translation_ = Vector3{ 350.0f, 598.0f, 0.0f };
	sprite_Target_.UpdateMatrix();
	textureHandle_target_ = textureManager_->LoadTexture("resources/Target/bossTarget.png");

	itemGaugeSprites_.clear();
	for (int i = 0; i < 3; i++) {
		Sprite* sprite = new Sprite();
		sprite->Initialize(Vector4{ 0.0f, 0.0f, 0.0f, 1.0f }, Vector4{ 0.0f, 128.0f, 0.0f, 1.0f }, Vector4{ 256.0f, 0.0f, 0.0f, 1.0f }, Vector4{ 256.0f, 128.0f, 0.0f, 1.0f });
		itemGaugeSprites_.emplace_back(sprite);
		worldTransform_itemGauge_[i].Initialize();
		worldTransform_itemGauge_[i].scale_ = Vector3{ 0.5f, 0.5f, 1.0f };
		worldTransform_itemGauge_[i].translation_ = Vector3{ 120.0f * float(i), 50.0f, 1.0f };
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

	pause_ = std::make_unique<Pause>();
	pause_->Initialize();
	isPause_ = false;

}

void GameBossState::Update()
{
	joyStatePre = joyState;
	input->GetJoystickState(0, joyState);

	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_START && !(joyStatePre.Gamepad.wButtons & XINPUT_GAMEPAD_START))
	{
		if (!pauseRelease_)
		{
			isPause_ = !isPause_;
			pauseRelease_ = true;
		}
		pause_->SetIsTutorial(false);

	}
	else {
		pauseRelease_ = false;
	}

	if (!isPause_) {

		ground_->Update();

		skydome_->Updata();

		player->Update();

		boss_->Update();

		followCamera->SetIsStickPre(player->GetIsStickRight(), player->GetIsStickLeft());

		followCamera->Update();
		viewProjection_ = followCamera->GetViewProjection();

		viewProjection_.UpdateMatrix();

		collisionManager_->AddBoxCollider(player.get());
		collisionManager_->AddBoxCollider(ground_.get());
		collisionManager_->AddBoxCollider(boss_.get());

		collisionManager_->CheckAllCollisions();
		collisionManager_->ClearCollider();

		worldTransform_item_.scale_.x = itemCount * 0.374f;
		worldTransform_item_.UpdateMatrix();

		if (player->GetIsDead() == true)
		{
			StateNo = 4;
			ImGui::Begin("Dead");
			//ImGui::Text("%d", StateNo);
			//ImGui::DragFloat3("itemWorldTransform", &itemWorldTransform_[6].translation_.x, 1.0f);
			ImGui::End();
		}

		if (boss_->GetIsDead() == true)
		{
			StateNo = 3;
			ImGui::Begin("Hit");
			//ImGui::Text("%d", StateNo);
			//ImGui::DragFloat3("itemWorldTransform", &itemWorldTransform_[6].translation_.x, 1.0f);
			ImGui::End();
		}
		particle->Update();


	}

	else {
		if (pause_->GetLeft()) {
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				if (!(joyStatePre.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
					StateNo = 0;
				}
			}
		}

		pause_->Update();
	}
	

}

void GameBossState::Draw()
{
	ground_->Draw(viewProjection_);

	player->Draw(viewProjection_);

	boss_->Draw(viewProjection_);

	skydome_->Draw(viewProjection_);

	speedSprite_->Draw(worldTransform_speed_, textureHandle_item_[2]);

	itemSprite_->Draw(worldTransform_item_, textureHandle_item_[1]);
	for (int i = 0; auto & sprite : itemGaugeSprites_) {
		sprite->Draw(worldTransform_itemGauge_[i], textureHandle_item_[0]);
		i++;
	}

	targetSprite_->Draw(sprite_Target_, textureHandle_target_);

	if (isPause_) {
		pause_->Draw();
	}


}
