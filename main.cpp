#include"Scenes/Manager/GameManager.h"
int GameState::StateNo;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	GameManager* gameManager = new GameManager();
	gameManager->Run();
	return 0;
}
