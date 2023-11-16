#include "Scenes/State/GamePlayState.h"

void GamePlayState::Initialize()
{
	
}

void GamePlayState::Update()
{
	ImGui::Begin("Play");

	ImGui::End();
}

void GamePlayState::Draw()
{
	//3Dモデル描画ここから
	
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
