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

	bossModel_.reset(Model::CreateModelFromObj("resources/Cube", "Cube.obj"));
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
}

void GameBossState::Update()
{
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

void GameBossState::Draw()
{
	ground_->Draw(viewProjection_);

	player->Draw(viewProjection_);

	boss_->Draw(viewProjection_);

	//skydome_->Draw(viewProjection_);

	particle->PreDraw();
	particle->Draw(viewProjection_);
}
